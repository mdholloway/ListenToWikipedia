package org.mdholloway.listentowikipedia.audio

import android.content.Context
import android.util.Log
import javax.inject.Inject

class OboeAudioPlayer
    @Inject
    constructor(
        private val context: Context,
    ) : AudioEngine {
        companion object {
            private const val TAG = "OboeAudioPlayer"

            init {
                System.loadLibrary("oboe_audio_player")
            }
        }

        private var isInitialized = false

        override fun start(): Boolean {
            if (!isInitialized) {
                isInitialized = initPlayer(context)
                if (!isInitialized) {
                    Log.e(TAG, "Failed to initialize Oboe audio player")
                    return false
                }
                Log.i(TAG, "Oboe audio player started successfully")
            }
            return isInitialized
        }

        override fun stop() {
            if (isInitialized) {
                shutdownPlayer()
                isInitialized = false
                Log.i(TAG, "Oboe audio player stopped")
            }
        }

        override fun playWikipediaEdit(
            sizeBytes: Int,
            isAddition: Boolean,
            volume: Float,
        ) {
            if (isInitialized) {
                playWikipediaEditNative(sizeBytes, isAddition, volume)
            } else {
                Log.w(TAG, "Cannot play sound: player not initialized")
            }
        }

        private external fun initPlayer(context: Context): Boolean

        private external fun shutdownPlayer()

        private external fun playWikipediaEditNative(
            sizeBytes: Int,
            isAddition: Boolean,
            volume: Float,
        )
    }
