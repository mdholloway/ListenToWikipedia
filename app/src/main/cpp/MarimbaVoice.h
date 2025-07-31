//
// Created by mdh on 7/27/25.
//

#ifndef LISTEN_TO_WIKIPEDIA_MARIMBAVOICE_H
#define LISTEN_TO_WIKIPEDIA_MARIMBAVOICE_H

#pragma once
#include "faust/dsp/dsp.h"
#include "faust/gui/PrintUI.h"
#include "Marimba.cpp"
#include <memory>
#include <vector>

class MarimbaVoice {
    std::unique_ptr<Marimba> dsp;
    std::unique_ptr<PrintUI> dummyUI;

    int sampleRate;
    int framesElapsed = 0;
    bool done = false;

    // Member variables to hold the current control values for each Faust input
    float currentFreq;
    float currentStrikePosition;
    float currentStrikeCutoff;
    float currentStrikeSharpness;
    float currentGain;
    float currentTrigger;

public:
    static constexpr int kVoiceDurationFrames = 48000;  // e.g. 1s @ 48kHz
    static constexpr int kVoiceReleaseFrames = 24000;   // Additional time for note decay after trigger release (0.5s)

    MarimbaVoice(int sr, float freq, float velocity) : sampleRate(sr) {
        dsp = std::make_unique<Marimba>();
        dummyUI = std::make_unique<PrintUI>();

        dsp->buildUserInterface(dummyUI.get());
        dsp->init(sampleRate);

        /* ui->setParamValue("/freq", freq);
        ui->setParamValue("/velocity", velocity);
        ui->setParamValue("/gate", 1.0f); */

        // Initialize the control values for the Faust DSP's inputs
        currentFreq = freq;
        currentGain = velocity;
        currentTrigger = 1.0f;

        // Provide some reasonable default values for the other inputs.
        // You might want to make these configurable or derive them more intelligently.
        currentStrikePosition = 0.0f;
        currentStrikeCutoff = 7000.0f;
        currentStrikeSharpness = 0.25f;
    }

    void render(float* outputBuffer, int numFrames, int numChannels) {
        // --- 1. Prepare Outputs for DSP ---
        std::vector<float*> dspOutputs(numChannels);
        for (int ch = 0; ch < numChannels; ++ch) {
            dspOutputs[ch] = outputBuffer + ch;
        }

        // --- 2. Prepare Inputs for DSP ---
        // Marimba has 6 input channels. Each needs a buffer of numFrames samples.
        // We use std::vector<std::vector<float>> to manage contiguous memory for each input.
        std::vector<std::vector<float>> inputBuffers(6, std::vector<float>(numFrames));

        // Fill each input buffer with the current control value for all frames in this block.
        for (int i = 0; i < numFrames; ++i) {
            inputBuffers[0][i] = currentFreq;
            inputBuffers[1][i] = currentStrikePosition;
            inputBuffers[2][i] = currentStrikeCutoff;
            inputBuffers[3][i] = currentStrikeSharpness;
            inputBuffers[4][i] = currentGain;
            inputBuffers[5][i] = currentTrigger;
        }

        // Create an array of raw pointers to the data of these input buffers.
        std::vector<float*> dspInputs(6);
        for (int i = 0; i < 6; ++i) {
            dspInputs[i] = inputBuffers[i].data();
        }

        // --- 3. Call Faust's compute method ---
        // This is where the actual sound synthesis happens.
        dsp->compute(numFrames, dspInputs.data(), dspOutputs.data());

        // --- 4. Manage Voice Lifetime and Gate ---
        framesElapsed += numFrames;

        // Turn off the gate after the initial trigger duration
        if (framesElapsed >= kVoiceDurationFrames) {
            currentTrigger = 0.0f; // Signal to the DSP to start the release phase
        }

        // Mark the voice as done after the trigger duration plus a release grace period
        if (framesElapsed > kVoiceDurationFrames + kVoiceReleaseFrames) {
            done = true;
        }
    }

    bool isDone() const { return done; }
};

#endif //LISTEN_TO_WIKIPEDIA_MARIMBAVOICE_H
