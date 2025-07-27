#include <jni.h>
#include <string>
#include "SimpleOboePlayer.h"
#include <android/log.h>

static SimpleOboePlayer *player = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_OboeAudioPlayer_initPlayer(JNIEnv* env, jobject /* this */) {
    if (player == nullptr) {
        player = new SimpleOboePlayer();
        player->start();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_OboeAudioPlayer_playEventSound(
    JNIEnv* env,
    jobject /* this */,
    jint diff,
    jboolean isBot,
    jboolean isIpAddress
) {
    if (player != nullptr) {
        player->playEventSound(static_cast<int>(diff), static_cast<bool>(isBot), static_cast<bool>(isIpAddress));
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_OboeAudioPlayer_shutdownPlayer(JNIEnv* env, jobject /* this */) {
    if (player != nullptr) {
        player->stop();
        delete player;
        player = nullptr;
    }
}
