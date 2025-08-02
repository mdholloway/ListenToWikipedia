#include "SimpleOboePlayer.h"
#include <android/log.h>
#include <cmath>
#include <algorithm>

#define TAG "SimpleOboePlayer"


SimpleOboePlayer::SimpleOboePlayer() :
    oboeaudio(48000), // TODO: Don't hardcode the sample rate
    mSoundDurationMillis(150),
    mAudioController(new APIUI()),
    mStandardBellDSP(new mydsp()) {

    this->init("simpleOboePlayer", mStandardBellDSP);
    mStandardBellDSP->buildUserInterface(mAudioController);

    mAudioController->setParamValue("/standardBell/gain", 0.4f); // Ensure a reasonable gain
}

SimpleOboePlayer::~SimpleOboePlayer() {
    delete mAudioController;
}

void SimpleOboePlayer::playEventSound(int diff, bool isBot, bool isIpAddress) {
    std::lock_guard<std::mutex> lock(mLock);

    // TODO: Randomize?
    mAudioController->setParamValue("/standardBell/exPos", 0.0f);

    // TODO: Vary with diff size
    mAudioController->setParamValue("/standardBell/hammerHardness", 0.9f);
    mAudioController->setParamValue("/standardBell/hammerSize", 0.3f);

    mAudioController->setParamValue("/standardBell/gate", 1.0f);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    mAudioController->setParamValue("/standardBell/gate", 0.0f);
}
