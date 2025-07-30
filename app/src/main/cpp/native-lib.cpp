#include <jni.h>
#include <string>
#include "AudioEngine.h"
#include <android/log.h>

static AudioEngine *player = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_AudioEngine_initNativeAudioEngine(JNIEnv* env, jobject /* this */) {
    if (player == nullptr) {
        player = new AudioEngine();
        player->start();
    }

}

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_AudioEngine_triggerMarimbaNote(
    JNIEnv* env,
    jobject /* this */,
    jint diff
) {
    if (player != nullptr) {
        player->triggerMarimbaNote(static_cast<int>(diff));
    }
}


//extern "C" JNIEXPORT void JNICALL
//Java_org_mdholloway_listentowikipedia_audio_AudioEngine_triggerNylonGuitarNote(
//    JNIEnv* env,
//    jobject /* this */,
//    jint diff
//) {
//    if (player != nullptr) {
//        player->triggerMarimbaNote(static_cast<int>(diff));
//    }
//}

extern "C" JNIEXPORT void JNICALL
Java_org_mdholloway_listentowikipedia_audio_AudioEngine_shutdownNativeAudioEngine(JNIEnv* env, jobject /* this */) {
    if (player != nullptr) {
        player->stop();
        delete player;
        player = nullptr;
    }
}
