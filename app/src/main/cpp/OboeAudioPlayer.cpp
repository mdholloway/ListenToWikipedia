#include "OboeAudioPlayer.h"
#include <android/log.h>
#include <cmath>
#include <algorithm>

#define TAG "OboeAudioPlayer"


OboeAudioPlayer::OboeAudioPlayer() :
    oboeaudio(48000), // TODO: Don't hardcode the sample rate
    mAudioController(new APIUI()),
    mStandardBellDSP(new mydsp()) {

    this->init(TAG, mStandardBellDSP);
    mStandardBellDSP->buildUserInterface(mAudioController);

    mAudioController->setParamValue("/standardBell/gain", 0.4f); // Ensure a reasonable gain
}

OboeAudioPlayer::~OboeAudioPlayer() {
    delete mAudioController;
}

void OboeAudioPlayer::playEventSound(int diff, bool isBot, bool isIpAddress) {
    std::lock_guard<std::mutex> lock(mLock);

    // TODO: Randomize?
    mAudioController->setParamValue("/standardBell/exPos", 0.0f);

    // TODO: Vary with diff size
    mAudioController->setParamValue("/standardBell/hammerHardness", 0.9f);
    mAudioController->setParamValue("/standardBell/hammerSize", 0.3f);

    mAudioController->setParamValue("/standardBell/gate", 1.0f);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    mAudioController->setParamValue("/standardBell/gate", 0.0f);
}
