package org.mdholloway.listentowikipedia.network

import android.content.Context
import android.content.pm.PackageManager
import android.util.Log
import dagger.hilt.android.scopes.ActivityScoped
import io.ktor.client.HttpClient
import io.ktor.client.engine.cio.CIO
import io.ktor.client.plugins.defaultRequest
import io.ktor.client.plugins.sse.SSE
import io.ktor.client.plugins.sse.sse
import io.ktor.sse.ServerSentEvent
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.asSharedFlow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.flow
import kotlinx.coroutines.flow.flowOn
import kotlinx.coroutines.flow.launchIn
import kotlinx.serialization.json.Json
import org.mdholloway.listentowikipedia.R
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import javax.inject.Inject

@ActivityScoped
class SseManager
    @Inject
    constructor(
        private val context: Context,
    ) {
        companion object {
            private const val TAG = "SseManager"
            private const val RC_STREAM_URL = "https://stream.wikimedia.org/v2/stream/recentchange"
        }

        private var client: HttpClient? = null
        private var connectionJob: Job? = null
        private val json = Json { ignoreUnknownKeys = true }

        private val _recentChangeEvents = MutableSharedFlow<RecentChangeEvent>()
        val recentChangeEvents: Flow<RecentChangeEvent> = _recentChangeEvents.asSharedFlow()

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
                // Create new HttpClient for this connection
                client = createHttpClient()

                connectionJob = startSseConnection().launchIn(scope)
                Log.i(TAG, "SSE connection started successfully")
                return true
            } catch (e: Exception) {
                Log.e(TAG, "Failed to start SSE connection", e)
                return false
            }
        }

        /**
         * Stops the SSE connection and closes the HTTP client. Safe to call multiple times.
         */
        fun stop() {
            connectionJob?.cancel()
            connectionJob = null

            client?.close()
            client = null

            Log.i(TAG, "SSE connection stopped and client closed")
        }

        /**
         * Returns whether the SSE connection is currently active
         */
        fun isConnected(): Boolean = connectionJob?.isActive == true

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

        private fun startSseConnection(): Flow<Unit> =
            flow<Unit> {
                client?.let { httpClient ->
                    httpClient.sse(RC_STREAM_URL) {
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
                .catch<Unit> { e ->
                    Log.e(TAG, "SSE connection error", e)
                }
    }
