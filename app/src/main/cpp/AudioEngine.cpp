#include "AudioEngine.h"
#include <android/log.h>
#include <cmath>
#include <algorithm>

#define TAG "AudioEngine"

namespace {
    float clamp(float x, float min, float max) {
        return std::max(min, std::min(x, max));
    }

    float scaleLog(float value, float minInput, float maxInput, float minOutput, float maxOutput) {
        float logMin = std::log(minInput);
        float logMax = std::log(maxInput);
        float logVal = std::log(clamp(value, minInput, maxInput));
        float t = (logVal - logMin) / (logMax - logMin);
        return minOutput + (1.0f - t) * (maxOutput - minOutput);  // small → high
    }
}


AudioEngine::AudioEngine()  {
    setupAudioStream();
}

AudioEngine::~AudioEngine() {
    stop();
}

void AudioEngine::setupAudioStream() {
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

void AudioEngine::triggerMarimbaNote(int diff) {
    float freq = scaleLog(diff, 1, 5000, 200.0f, 1000.0f);
    float velocity = scaleLog(diff, 1, 5000, 0.3f, 1.0f);
    marimbaVoices.push_back(std::make_unique<MarimbaVoice>(mAudioStream->getSampleRate(), freq, velocity));
}

/*void AudioEngine::triggerNylonGuitarNote(int diff) {
    float freq = scaleLog(diff, 1, 5000, 200.0f, 1000.0f);
    float velocity = scaleLog(diff, 1, 5000, 0.3f, 1.0f);
    nylonGuitarVoices.push_back(std::make_unique<NylonGuitarVoice>(mAudioStream->getSampleRate(), freq, velocity));
}*/

void AudioEngine::start() {
    if (mAudioStream) {
        oboe::Result result = mAudioStream->requestStart();
        if (result != oboe::Result::OK) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to start stream: %s",
                                oboe::convertToText(result));
        }
    }
}

void AudioEngine::stop() {
    if (mAudioStream) {
        mAudioStream->requestStop();
        mAudioStream->close();
        mAudioStream.reset(); // Release the ManagedStream
    }
}

oboe::DataCallbackResult AudioEngine::onAudioReady(
    oboe::AudioStream *audioStream,
    void *audioData,
    int32_t numFrames
) {
    int numChannels = audioStream->getChannelCount();
    auto* output = static_cast<float*>(audioData);
    memset(output, 0, sizeof(float) * numFrames * numChannels);

    // Mix active voices
    for (auto& voice : marimbaVoices) {
        std::vector<float> tempBuffer(numFrames * numChannels, 0.0f);
        voice->render(tempBuffer.data(), numFrames, numChannels);
        for (int i = 0; i < numFrames * numChannels; ++i) {
            output[i] += tempBuffer[i];
        }
    }

    /*for (auto& voice : nylonGuitarVoices) {
        std::vector<float> tempBuffer(numFrames * numChannels, 0.0f);
        voice->render(tempBuffer.data(), numFrames, numChannels);
        for (int i = 0; i < numFrames * numChannels; ++i) {
            output[i] += tempBuffer[i];
        }
    }*/

    // Remove finished voices
    marimbaVoices.erase(
            std::remove_if(marimbaVoices.begin(), marimbaVoices.end(),
                           [](const std::unique_ptr<MarimbaVoice>& v) { return v->isDone(); }),
            marimbaVoices.end()
    );

    /*nylonGuitarVoices.erase(
        std::remove_if(nylonGuitarVoices.begin(), nylonGuitarVoices.end(),
            [](const std::unique_ptr<NylonGuitarVoice>& v) { return v->isDone(); }),
        nylonGuitarVoices.end()
    );*/

    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::onErrorAfterClose(
    oboe::AudioStream *audioStream,
    oboe::Result error
) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "Error after close: %s",
                        oboe::convertToText(error));
}
