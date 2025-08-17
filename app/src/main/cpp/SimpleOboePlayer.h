
#ifndef OBOE_SIMPLEOBOEPLAYER_H
#define OBOE_SIMPLEOBOEPLAYER_H

#include <oboe/Oboe.h>
#include <mutex>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>
#include <jni.h>

// Forward declarations
class AudioSample;
class Voice;

class SimpleOboePlayer : public oboe::AudioStreamCallback {
public:
    SimpleOboePlayer();
    ~SimpleOboePlayer() override;

    bool loadSamples(JNIEnv* env, jobject context);
    void start();
    void stop();
    void playWikipediaEdit(int sizeBytes, bool isAddition, float volume = 1.0f);

    // Oboe AudioStreamCallback overrides
    oboe::DataCallbackResult onAudioReady(
            oboe::AudioStream *audioStream,
            void *audioData,
            int32_t numFrames
    ) override;

    void onErrorAfterClose(
            oboe::AudioStream *audioStream,
            oboe::Result error
    ) override;

private:
    static constexpr int MAX_VOICES = 32;
    static constexpr double MAX_PITCH = 100.0;
    static constexpr double LOG_USED = 1.0715307808111486871978099;
    
    oboe::ManagedStream mAudioStream;
    std::mutex mLock;
    std::vector<std::unique_ptr<Voice>> mVoices;
    
    // Sample storage
    std::vector<std::unique_ptr<AudioSample>> mCelestaSamples;  // 27 samples
    std::vector<std::unique_ptr<AudioSample>> mClavSamples;     // 27 samples  
    std::vector<std::unique_ptr<AudioSample>> mSwellSamples;    // 3 samples

    void setupAudioStream();
    bool loadSampleFromAsset(JNIEnv* env, jobject context, const char* filename, std::unique_ptr<AudioSample>& sample);
    int calculateSampleIndex(int sizeBytes);
    Voice* findFreeVoice();
};

// Simple audio sample container
class AudioSample {
public:
    std::vector<float> data;
    int sampleRate;
    int channels;
    
    AudioSample() : sampleRate(44100), channels(1) {}
};

// Voice for polyphonic playback
class Voice {
public:
    Voice() : isActive(false), position(0), sample(nullptr), volume(1.0f) {}
    
    bool isActive;
    size_t position;
    AudioSample* sample;
    float volume;
    
    void trigger(AudioSample* sampleToPlay, float vol) {
        sample = sampleToPlay;
        volume = vol;
        position = 0;
        isActive = true;
    }
    
    void stop() {
        isActive = false;
        sample = nullptr;
        position = 0;
    }
    
    float getNextSample() {
        if (!isActive || !sample || position >= sample->data.size()) {
            isActive = false;
            return 0.0f;
        }
        
        float sampleValue = sample->data[position] * volume;
        position++;
        
        if (position >= sample->data.size()) {
            isActive = false;
        }
        
        return sampleValue;
    }
};

#endif //OBOE_SIMPLEOBOEPLAYER_H