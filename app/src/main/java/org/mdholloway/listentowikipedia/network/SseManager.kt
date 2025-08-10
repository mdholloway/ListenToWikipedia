package org.mdholloway.listentowikipedia.network

import android.content.Context
import android.content.pm.PackageManager
import android.util.Log
import io.ktor.client.HttpClient
import io.ktor.client.engine.cio.CIO
import io.ktor.client.plugins.defaultRequest
import io.ktor.client.plugins.sse.SSE
import io.ktor.client.plugins.sse.sse
import io.ktor.sse.ServerSentEvent
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.asSharedFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.flow
import kotlinx.coroutines.flow.flowOn
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.retry
import kotlinx.serialization.json.Json
import org.mdholloway.listentowikipedia.R
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.ui.state.ConnectionState
import javax.inject.Inject
import javax.inject.Singleton
import kotlin.math.min
import kotlin.math.pow
import kotlin.random.Random

@Singleton
class SseManager
    @Inject
    constructor(
        private val context: Context,
    ) {
        companion object {
            private const val TAG = "SseManager"
            private const val RC_STREAM_URL = "https://stream.wikimedia.org/v2/stream/recentchange"
            private const val MAX_RETRY_ATTEMPTS = 5
            private const val BASE_RETRY_DELAY_MS = 1000L
            private const val MAX_RETRY_DELAY_MS = 30000L
        }

        private var client: HttpClient? = null
        private var connectionJob: Job? = null
        private val json = Json { ignoreUnknownKeys = true }
        private var retryCount = 0
        private var lastSuccessfulConnection: Long? = null

        private val _recentChangeEvents = MutableSharedFlow<RecentChangeEvent>()
        val recentChangeEvents: Flow<RecentChangeEvent> = _recentChangeEvents.asSharedFlow()

        private val _connectionState = MutableStateFlow<ConnectionState>(ConnectionState.Disconnected)
        val connectionState: Flow<ConnectionState> = _connectionState.asStateFlow()

        /**
         * Starts the SSE connection. Safe to call multiple times.
         * @param scope CoroutineScope to launch the connection in
         * @return true if connection started successfully, false otherwise
         */
        fun start(scope: CoroutineScope): Boolean {
            if (connectionJob?.isActive == true) {
                Log.i(TAG, "SSE connection already active, skipping start.")
                return true
            }

            try {
                _connectionState.value = ConnectionState.Connecting
                retryCount = 0

                // Create new HttpClient for this connection
                client = createHttpClient()

                connectionJob = startSseConnectionWithRetry().launchIn(scope)
                Log.i(TAG, "SSE connection started successfully")
                return true
            } catch (e: Exception) {
                Log.e(TAG, "Failed to start SSE connection", e)
                _connectionState.value =
                    ConnectionState.Error(
                        message = "Failed to start connection: ${e.message}",
                        canRetry = true,
                    )
                return false
            }
        }

        /**
         * Stops the SSE connection and closes the HTTP client. Safe to call multiple times.
         */
        fun stop() {
            connectionJob?.cancel()
            connectionJob = null
            retryCount = 0

            client?.close()
            client = null

            _connectionState.value = ConnectionState.Disconnected
            Log.i(TAG, "SSE connection stopped and client closed")
        }

        /**
         * Returns whether the SSE connection is currently active
         */
        fun isConnected(): Boolean = connectionJob?.isActive == true

        fun retryConnection(scope: CoroutineScope) {
            if (connectionJob?.isActive != true) {
                Log.i(TAG, "Manually retrying SSE connection")
                start(scope)
            }
        }

        private fun createHttpClient(): HttpClient =
            HttpClient(CIO) {
                install(SSE)
                defaultRequest {
                    val appName = context.getString(R.string.app_name)
                    val appVersion =
                        try {
                            val packageInfo = context.packageManager.getPackageInfo(context.packageName, 0)
                            packageInfo.versionName
                        } catch (e: PackageManager.NameNotFoundException) {
                            "Unknown"
                        }
                    val contactInfo = context.getString(R.string.contact_email)
                    headers.append("User-Agent", "$appName/$appVersion ($contactInfo)")
                }
            }

        private fun startSseConnectionWithRetry(): Flow<Unit> =
            startSseConnection()
                .retry { cause ->
                    retryCount++
                    Log.w(TAG, "SSE connection failed (attempt $retryCount/$MAX_RETRY_ATTEMPTS)", cause)

                    val shouldRetry = retryCount < MAX_RETRY_ATTEMPTS
                    if (shouldRetry) {
                        val delayMs = calculateRetryDelay(retryCount)
                        _connectionState.value =
                            ConnectionState.Error(
                                message = "Connection lost, retrying in ${delayMs / 1000}s...",
                                canRetry = true,
                                lastSuccessfulConnection = lastSuccessfulConnection,
                            )

                        delay(delayMs)
                        true
                    } else {
                        _connectionState.value =
                            ConnectionState.Error(
                                message = "Connection failed after $MAX_RETRY_ATTEMPTS attempts",
                                canRetry = true,
                                lastSuccessfulConnection = lastSuccessfulConnection,
                            )
                        false
                    }
                }

        private fun startSseConnection(): Flow<Unit> =
            flow<Unit> {
                client?.let { httpClient ->
                    _connectionState.value = ConnectionState.Connecting

                    httpClient.sse(RC_STREAM_URL) {
                        // Connection successful
                        _connectionState.value = ConnectionState.Connected
                        lastSuccessfulConnection = System.currentTimeMillis()
                        retryCount = 0 // Reset retry count on successful connection
                        Log.i(TAG, "SSE connection established successfully")

                        incoming.collect { event: ServerSentEvent ->
                            try {
                                if (event.data != null) {
                                    val recentChangeEvent = json.decodeFromString<RecentChangeEvent>(event.data!!)
                                    _recentChangeEvents.emit(recentChangeEvent)
                                }
                            } catch (e: Exception) {
                                Log.e(TAG, "Error deserializing SSE event", e)
                            }
                        }
                    }
                }
            }.flowOn(Dispatchers.IO)

        private fun calculateRetryDelay(attempt: Int): Long {
            val exponentialDelay = BASE_RETRY_DELAY_MS * (2.0.pow(attempt - 1)).toLong()
            val jitter = Random.nextLong(0, 1000) // Add 0-1s jitter
            return min(exponentialDelay + jitter, MAX_RETRY_DELAY_MS)
        }
    }
