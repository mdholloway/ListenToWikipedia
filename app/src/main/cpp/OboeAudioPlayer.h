#ifndef OBOE_AUDIO_PLAYER_H
#define OBOE_AUDIO_PLAYER_H

#include "faust/audio/oboe-dsp.h"
#include "faust/gui/APIUI.h"
#include <mutex>
#include <chrono>
#include "StandardBell.cpp"

class OboeAudioPlayer : public oboeaudio {
public:
    OboeAudioPlayer();
    ~OboeAudioPlayer();

    void playEventSound(int diff, bool isBot, bool isIpAddress);

private:
    APIUI* mAudioController;
    mydsp* mStandardBellDSP;
    std::mutex mLock;
    std::chrono::time_point<std::chrono::system_clock> mSoundStartTime;
};

#endif //OBOE_AUDIO_PLAYER_H