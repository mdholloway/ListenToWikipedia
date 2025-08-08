package org.mdholloway.listentowikipedia.audio

import android.util.Log
import com.DspFaust.DspFaust
import dagger.hilt.android.scopes.ActivityScoped
import javax.inject.Inject

@ActivityScoped
class AudioManager
    @Inject
    constructor(
        private val dspFaust: DspFaust,
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
                isStarted = dspFaust.start()
                Log.i(TAG, "Audio engine started: $isStarted")
            }
            return isStarted
        }

        /**
         * Stops the audio engine. Safe to call multiple times.
         */
        fun stop() {
            if (isStarted) {
                dspFaust.stop()
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
                dspFaust.keyOn(midiNote, velocity)
            } else {
                Log.w(TAG, "Cannot play note: audio engine not started")
            }
        }

        /**
         * Returns whether the audio engine is currently running
         */
        fun isRunning(): Boolean = isStarted
    }
