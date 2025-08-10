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
         * Plays a MIDI note if the audio engine is running.
         * @param midiNote MIDI note number (0-127)
         * @param velocity Note velocity (0-127)
         */
        fun playNote(
            midiNote: Int,
            velocity: Int,
        ) {
            if (isStarted) {
                audioEngine.keyOn(midiNote, velocity)
            } else {
                Log.w(TAG, "Cannot play note: audio engine not started")
            }
        }

        /**
         * Returns whether the audio engine is currently running
         */
        fun isRunning(): Boolean = isStarted
    }
