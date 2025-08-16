package org.mdholloway.listentowikipedia.audio

interface AudioEngine {
    fun start(): Boolean

    fun stop()

    fun playWikipediaEdit(
        sizeBytes: Int,
        isAddition: Boolean = true,
        volume: Float = 1.0f,
    )
}
