#ifndef OBOE_SIMPLEOBOEPLAYER_H
#define OBOE_SIMPLEOBOEPLAYER_H

#include "faust/audio/oboe-dsp.h"
#include "faust/gui/APIUI.h"
#include <oboe/Oboe.h>
#include <mutex>
#include <chrono>
#include "StandardBell.cpp"

class SimpleOboePlayer : public oboeaudio {
public:
    SimpleOboePlayer();
    ~SimpleOboePlayer();

    void playEventSound(int diff, bool isBot, bool isIpAddress);

private:
    APIUI* mAudioController;
    mydsp* mStandardBellDSP;
    std::mutex mLock;
    std::chrono::time_point<std::chrono::system_clock> mSoundStartTime;
    long mSoundDurationMillis{};
}; 

#endif //OBOE_SIMPLEOBOEPLAYER_H