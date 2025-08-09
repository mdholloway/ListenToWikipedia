package org.mdholloway.listentowikipedia.audio

interface AudioEngine {
    fun start(): Boolean

    fun stop()

    fun keyOn(
        midiNote: Int,
        velocity: Int,
    )
}
