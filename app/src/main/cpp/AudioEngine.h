#ifndef OBOE_AUDIOENGINE_H
#define OBOE_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include <mutex>
#include <chrono>
#include "MarimbaVoice.h"
//#include "NylonGuitarVoice.h"

class AudioEngine : public oboe::AudioStreamCallback {
public:
    AudioEngine();
    ~AudioEngine();

    void start();
    void stop();
    void triggerMarimbaNote(int diff);
    //void triggerNylonGuitarNote(int diff);

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
    std::mutex mLock;
    //std::vector<std::unique_ptr<NylonGuitarVoice>> nylonGuitarVoices;
    std::vector<std::unique_ptr<MarimbaVoice>> marimbaVoices;

    void setupAudioStream();
}; 

#endif //OBOE_AUDIOENGINE_H