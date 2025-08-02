#include "SimpleOboePlayer.h"
#include <android/log.h>
#include <cmath>
#include <algorithm>

#define TAG "SimpleOboePlayer"


SimpleOboePlayer::SimpleOboePlayer() :
    oboeaudio(48000), // TODO: Don't hardcode the sample rate
    mSoundDurationMillis(150),
    mAudioController(new APIUI()),
    mSynthDSP(new mydsp()) {

    this->init("simpleOboePlayer", mSynthDSP);
    mSynthDSP->buildUserInterface(mAudioController);

    mAudioController->setParamValue("/synth/gate", 1.0f); // Gate open
    mAudioController->setParamValue("/synth/gain", 0.5f); // Ensure a reasonable gain
    mAudioController->setParamValue("/synth/freq", 440.0f); // Set a test frequency (e.g., A4)
    mAudioController->setParamValue("/synth/cutoff", 5000.0f); // Default for cutoff
    mAudioController->setParamValue("/synth/q", 5.0f); // Default for Q
}

SimpleOboePlayer::~SimpleOboePlayer() {
    delete mAudioController;
}

void SimpleOboePlayer::playEventSound(int diff, bool isBot, bool isIpAddress) {
    std::lock_guard<std::mutex> lock(mLock);

    // Inverted Pitch Mapping: Larger diff -> Lower pitch, Smaller diff -> Higher pitch
    // Using a logarithmic scale for more perceptually uniform pitch changes.
    // Base frequency for max diff (e.g., 500k bytes) = low pitch
    // Max frequency for min diff (e.g., 1 byte) = high pitch
    const double minFreq = 100.0; // Hz
    const double maxFreq = 1000.0; // Hz
    const int maxAbsDiff = 500000; // Max expected diff for scaling
    const int minAbsDiff = 1;     // Min expected diff

    int clampedDiff = std::max(minAbsDiff, std::min(abs(diff), maxAbsDiff));

    // Normalize diff to a 0-1 range where 0 is maxAbsDiff and 1 is minAbsDiff
    double normalizedDiff = 1.0 - (static_cast<double>(clampedDiff - minAbsDiff) / (maxAbsDiff - minAbsDiff));

    double logMinFreq = std::log(minFreq);
    double logMaxFreq = std::log(maxFreq);
    double logFreq = logMinFreq + (logMaxFreq - logMinFreq) * normalizedDiff;
    double actualFreq = std::exp(logFreq);

    mSoundStartTime = std::chrono::system_clock::now();
    mAudioController->setParamValue("/synth/freq", diff*10);

    __android_log_print(ANDROID_LOG_INFO, TAG,
                        "playEventSound: diff=%d, isBot=%d, isIpAddress=%d, freq=%.2f",
                        diff, isBot, isIpAddress, actualFreq);
}
