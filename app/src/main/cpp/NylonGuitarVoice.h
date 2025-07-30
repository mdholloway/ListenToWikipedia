//
// Created by mdh on 7/27/25.
//

#ifndef LISTEN_TO_WIKIPEDIA_NYLONGUITARVOICE_H
#define LISTEN_TO_WIKIPEDIA_NYLONGUITARVOICE_H

#pragma once
#include "NylonGuitar.cpp"
#include <memory>

class NylonGuitarVoice {
    std::unique_ptr<NylonGuitar> dsp;
    int sampleRate;
    int framesElapsed = 0;
    bool done = false;

public:
    static constexpr int kVoiceDurationFrames = 48000;  // e.g. 1s @ 48kHz

    NylonGuitarVoice(int sr, float freq, float velocity) : sampleRate(sr) {
        dsp = std::make_unique<NylonGuitar>();
        dsp->init(sampleRate);
        /* dsp->setParamValue("freq", freq);
        dsp->setParamValue("velocity", velocity);
        dsp->setParamValue("gate", 1.0f); */
    }

    void render(float* outputBuffer, int numFrames, int numChannels) {
        std::vector<float*> outputs(numChannels);
        for (int ch = 0; ch < numChannels; ++ch) {
            outputs[ch] = outputBuffer + ch;
        }

        dsp->compute(numFrames, nullptr, outputs.data());

        framesElapsed += numFrames;
        if (framesElapsed > kVoiceDurationFrames) {
            done = true;
        }
    }

    bool isDone() const { return done; }
};

#endif //LISTEN_TO_WIKIPEDIA_NYLONGUITARVOICE_H
