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
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.flow
import kotlinx.coroutines.flow.flowOn
import kotlinx.serialization.json.Json
import org.mdholloway.listentowikipedia.R
import org.mdholloway.listentowikipedia.model.RecentChangeEvent

class RecentChangesSseService(
    private val context: Context,
) {
    companion object {
        private const val TAG = "RecentChangesSseService"
        private const val RC_STREAM_URL = "https://stream.wikimedia.org/v2/stream/recentchange"
    }

    private val client =
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

    private val json = Json { ignoreUnknownKeys = true }

    /**
     * Connects to the Wikimedia RecentChanges stream and emits RecentChangeEvent objects.
     * The Flow will emit events as they are received.
     * It will complete if the connection is closed normally, or emit an error
     * if an exception occurs during connection or processing.
     */
    fun listenToRecentChanges(): Flow<RecentChangeEvent> =
        flow {
            client.sse(RC_STREAM_URL) {
                incoming.collect { event: ServerSentEvent ->
                    try {
                        if (event.data != null) {
                            val recentChangeEvent = json.decodeFromString<RecentChangeEvent>(event.data!!)
                            emit(recentChangeEvent)
                        }
                    } catch (e: Exception) {
                        Log.e(TAG, "Error deserializing SSE event", e)
                    }
                }
            }
        }.flowOn(Dispatchers.IO)
            .catch { e ->
                Log.e(TAG, "SSE connection error", e)
            }

    fun close() {
        client.close()
    }
}
