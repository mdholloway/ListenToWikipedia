package org.mdholloway.listentowikipedia.audio

class AudioEngine {

    init {
        System.loadLibrary("oboe_audio_player")
        initNativeAudioEngine()
    }
    private external fun initNativeAudioEngine()
    private external fun shutdownNativeAudioEngine()
    external fun triggerMarimbaNote(diff: Int)
    // external fun triggerNylonGuitarNote(diff: Int)

    fun release() {
        shutdownNativeAudioEngine()
    }
}