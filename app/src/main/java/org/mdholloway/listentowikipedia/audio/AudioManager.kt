package org.mdholloway.listentowikipedia.audio

import android.util.Log
import javax.inject.Inject
import javax.inject.Singleton

@Singleton
class AudioManager
    @Inject
    constructor(
        private val audioEngine: AudioEngine,
    ) {
        companion object {
            private const val TAG = "AudioManager"
        }

        private var isStarted = false

        /**
         * Starts the audio engine. Safe to call multiple times.
         * @return true if audio engine started successfully, false otherwise
         */
        fun start(): Boolean {
            if (!isStarted) {
                isStarted = audioEngine.start()
                Log.i(TAG, "Audio engine started: $isStarted")
            }
            return isStarted
        }

        /**
         * Stops the audio engine. Safe to call multiple times.
         */
        fun stop() {
            if (isStarted) {
                audioEngine.stop()
                isStarted = false
                Log.i(TAG, "Audio engine stopped")
            }
        }

        /**
         * Plays a sound for a Wikipedia edit with the given size in bytes.
         * Uses the same pitch calculation algorithm as the original Listen to Wikipedia web app.
         * @param sizeBytes The size of the edit in bytes
         * @param isAddition Whether this is an addition (true) or deletion (false)
         * @param volume Volume level (0.0-1.0)
         */
        fun playWikipediaEdit(
            sizeBytes: Int,
            isAddition: Boolean = true,
            volume: Float = 1.0f,
        ) {
            if (isStarted) {
                audioEngine.playWikipediaEdit(sizeBytes, isAddition, volume)
            } else {
                Log.w(TAG, "Cannot play Wikipedia edit sound: audio engine not started")
            }
        }

        /**
         * Returns whether the audio engine is currently running
         */
        fun isRunning(): Boolean = isStarted
    }
