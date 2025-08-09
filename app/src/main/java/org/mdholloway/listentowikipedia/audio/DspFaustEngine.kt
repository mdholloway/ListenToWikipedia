package org.mdholloway.listentowikipedia.audio

import com.DspFaust.DspFaust
import javax.inject.Inject

class DspFaustEngine
    @Inject
    constructor(
        private val dspFaust: DspFaust,
    ) : AudioEngine {
        override fun start(): Boolean = dspFaust.start()

        override fun stop() = dspFaust.stop()

        override fun keyOn(
            midiNote: Int,
            velocity: Int,
        ) {
            dspFaust.keyOn(midiNote, velocity)
        }
    }
