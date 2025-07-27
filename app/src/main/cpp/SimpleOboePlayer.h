#ifndef OBOE_SIMPLEOBOEPLAYER_H
#define OBOE_SIMPLEOBOEPLAYER_H

#include <oboe/Oboe.h>
#include <mutex>
#include <chrono>

class SimpleOboePlayer : public oboe::AudioStreamCallback {
public:
    SimpleOboePlayer();
    ~SimpleOboePlayer();

    void start();
    void stop();
    void playEventSound(int diff, bool isBot, bool isIpAddress);

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
    oboe::ManagedStream mAudioStream;
    double mPhase;
    double mFrequency;
    double mAmplitude;
    std::mutex mLock;
    std::chrono::time_point<std::chrono::system_clock> mSoundStartTime;
    long mSoundDurationMillis;
    int mWaveformType; // 0: Sine, 1: Square, 2: Triangle

    void setupAudioStream();
}; 

#endif //OBOE_SIMPLEOBOEPLAYER_H