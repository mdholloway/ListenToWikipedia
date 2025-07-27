package org.mdholloway.listentowikipedia.audio

class OboeAudioPlayer {

    init {
        System.loadLibrary("oboe_audio_player")
        initPlayer()
    }

    private external fun initPlayer()
    private external fun shutdownPlayer()
    external fun playEventSound(diff: Int, isBot: Boolean, isIpAddress: Boolean)

    fun release() {
        shutdownPlayer()
    }
}