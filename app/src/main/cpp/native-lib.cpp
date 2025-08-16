#include <jni.h>
#include <string>
#include "SimpleOboePlayer.h"
#include <android/log.h>

static SimpleOboePlayer *player = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_OboeAudioPlayer_initPlayer(
        JNIEnv* env,
        jobject thiz,
        jobject context
) {
    if (player == nullptr) {
        player = new SimpleOboePlayer();
        if (!player->loadSamples(env, context)) {
            delete player;
            player = nullptr;
        }
        player->start();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_OboeAudioPlayer_playWikipediaEditNative(
        JNIEnv* env,
        jobject /* this */,
        jint sizeBytes,
        jboolean isAddition,
        jfloat volume
) {
    if (player != nullptr) {
        player->playWikipediaEdit(
            static_cast<int>(sizeBytes),
            static_cast<bool>(isAddition),
            static_cast<float>(volume)
        );
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