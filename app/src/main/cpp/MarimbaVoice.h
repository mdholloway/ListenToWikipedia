//
// Created by mdh on 7/27/25.
//

#ifndef LISTEN_TO_WIKIPEDIA_MARIMBAVOICE_H
#define LISTEN_TO_WIKIPEDIA_MARIMBAVOICE_H

#pragma once
#include "faust/dsp/dsp.h"
#include "faust/gui/MapUI.h"
#include "Marimba.cpp"
#include <memory>

class MarimbaVoice {
    std::unique_ptr<Marimba> dsp;
    std::unique_ptr<MapUI> ui;
    int sampleRate;
    int framesElapsed = 0;
    bool done = false;

public:
    static constexpr int kVoiceDurationFrames = 48000;  // e.g. 1s @ 48kHz

    MarimbaVoice(int sr, float freq, float velocity) : sampleRate(sr) {
        dsp = std::make_unique<Marimba>();
        ui = std::make_unique<MapUI>();

        dsp->buildUserInterface(ui.get());
        dsp->init(sampleRate);

        ui->setParamValue("/freq", freq);
        ui->setParamValue("/velocity", velocity);
        ui->setParamValue("/gate", 1.0f);
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

#endif //LISTEN_TO_WIKIPEDIA_MARIMBAVOICE_H
