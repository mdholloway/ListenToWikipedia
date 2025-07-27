#include "SimpleOboePlayer.h"
#include <android/log.h>
#include <cmath>
#include <algorithm>

#define TAG "SimpleOboePlayer"

SimpleOboePlayer::SimpleOboePlayer() :
    mPhase(0.0),
    mFrequency(440.0), // Default A4
    mAmplitude(0.0),   // Start silent
    mSoundDurationMillis(150),
    mWaveformType(0) {
    setupAudioStream();
}

SimpleOboePlayer::~SimpleOboePlayer() {
    stop();
}

void SimpleOboePlayer::setupAudioStream() {
    oboe::AudioStreamBuilder builder;
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(oboe::ChannelCount::Mono);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setCallback(this);
    builder.setDirection(oboe::Direction::Output);

    oboe::Result result = builder.openManagedStream(mAudioStream);
    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to open stream: %s",
                            oboe::convertToText(result));
    }
}

void SimpleOboePlayer::start() {
    if (mAudioStream) {
        oboe::Result result = mAudioStream->requestStart();
        if (result != oboe::Result::OK) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to start stream: %s",
                                oboe::convertToText(result));
        }
    }
}

void SimpleOboePlayer::stop() {
    if (mAudioStream) {
        mAudioStream->requestStop();
        mAudioStream->close();
        mAudioStream.reset(); // Release the ManagedStream
    }
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

    // Apply logarithmic scaling for pitch
    mFrequency = minFreq * std::pow((maxFreq / minFreq), normalizedDiff);

    // Waveform Type (Timbre)
    if (isBot) {
        mWaveformType = 1; // Square wave for bots
    } else if (isIpAddress) {
        mWaveformType = 2; // Triangle wave for unregistered users (IPs)
    } else {
        mWaveformType = 0; // Sine wave for registered users
    }

    mAmplitude = 0.2f; // Set amplitude to play the sound
    mSoundStartTime = std::chrono::system_clock::now();

    // Ensure stream is running
    if (mAudioStream && mAudioStream->getState() != oboe::StreamState::Started) {
        start();
    }
}

oboe::DataCallbackResult SimpleOboePlayer::onAudioReady(
    oboe::AudioStream *audioStream,
    void *audioData,
    int32_t numFrames
) {
    float *outputBuffer = static_cast<float *>(audioData);
    int32_t sampleRate = audioStream->getSampleRate();

    std::lock_guard<std::mutex> lock(mLock);

    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - mSoundStartTime).count();

    if (duration > mSoundDurationMillis) {
        mAmplitude = 0.0f; // Stop sound after duration
    }

    for (int i = 0; i < numFrames; ++i) {
        float sample = 0.0f;
        if (mAmplitude > 0.0f) {
            switch (mWaveformType) {
                case 0: // Sine wave
                    sample = static_cast<float>(sin(mPhase * 2.0 * M_PI));
                    break;
                case 1: // Square wave
                    sample = static_cast<float>((fmod(mPhase, 1.0) < 0.5) ? 1.0 : -1.0);
                    break;
                case 2: // Triangle wave
                    sample = static_cast<float>(2.0 * abs(fmod(mPhase, 1.0) - 0.5) - 1.0);
                    break;
            }
        }
        outputBuffer[i] = sample * mAmplitude;
        mPhase += mFrequency / sampleRate;
        if (mPhase > 1.0) {
            mPhase -= 1.0;
        }
    }
    return oboe::DataCallbackResult::Continue;
}

void SimpleOboePlayer::onErrorAfterClose(
    oboe::AudioStream *audioStream,
    oboe::Result error
) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "Error after close: %s",
                        oboe::convertToText(error));
}
