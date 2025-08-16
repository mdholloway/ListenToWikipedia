#include "SimpleOboePlayer.h"
#include <android/log.h>
#include <cmath>
#include <algorithm>
#include <random>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#define TAG "SimpleOboePlayer"

// Custom callbacks for libvorbisfile to read from Android assets
struct AssetData {
    AAsset* asset;
    off_t offset;
    off_t length;
};

static size_t assetReadCallback(void* ptr, size_t size, size_t nmemb, void* datasource) {
    AssetData* data = static_cast<AssetData*>(datasource);
    size_t bytesToRead = size * nmemb;
    size_t bytesRead = AAsset_read(data->asset, ptr, bytesToRead);
    return bytesRead / size; // vorbisfile expects number of items read
}

static int assetSeekCallback(void* datasource, ogg_int64_t offset, int whence) {
    AssetData* data = static_cast<AssetData*>(datasource);
    off_t newPos;
    
    switch (whence) {
        case SEEK_SET:
            newPos = offset;
            break;
        case SEEK_CUR:
            newPos = data->offset + offset;
            break;
        case SEEK_END:
            newPos = data->length + offset;
            break;
        default:
            return -1;
    }
    
    if (newPos < 0 || newPos > data->length) {
        return -1;
    }
    
    off_t result = AAsset_seek(data->asset, newPos, SEEK_SET);
    if (result == -1) {
        return -1;
    }
    
    data->offset = newPos;
    return 0;
}

static int assetCloseCallback(void* datasource) {
    AssetData* data = static_cast<AssetData*>(datasource);
    if (data->asset) {
        AAsset_close(data->asset);
        data->asset = nullptr;
    }
    return 0;
}

static long assetTellCallback(void* datasource) {
    AssetData* data = static_cast<AssetData*>(datasource);
    return data->offset;
}

SimpleOboePlayer::SimpleOboePlayer() {
    // Initialize voices
    mVoices.reserve(MAX_VOICES);
    for (int i = 0; i < MAX_VOICES; ++i) {
        mVoices.push_back(std::make_unique<Voice>());
    }
    
    setupAudioStream();
}

SimpleOboePlayer::~SimpleOboePlayer() {
    stop();
}

void SimpleOboePlayer::setupAudioStream() {
    oboe::AudioStreamBuilder builder;
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(oboe::ChannelCount::Stereo);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setCallback(this);
    builder.setDirection(oboe::Direction::Output);

    oboe::Result result = builder.openManagedStream(mAudioStream);
    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to open stream: %s",
                            oboe::convertToText(result));
    }
}

bool SimpleOboePlayer::loadSamples(JNIEnv* env, jobject context) {
    __android_log_print(ANDROID_LOG_INFO, TAG, "Loading audio samples...");
    
    // Reserve space for samples
    mCelestaSamples.reserve(27);
    mClavSamples.reserve(27);
    mSwellSamples.reserve(3);
    
    // Load celesta samples (c001.ogg to c027.ogg)
    for (int i = 1; i <= 27; ++i) {
        char filename[64];
        snprintf(filename, sizeof(filename), "sounds/celesta/c%03d.ogg", i);
        
        auto sample = std::make_unique<AudioSample>();
        if (loadSampleFromAsset(env, context, filename, sample)) {
            mCelestaSamples.push_back(std::move(sample));
        } else {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to load celesta sample: %s", filename);
            return false;
        }
    }
    
    // Load clav samples (c001.ogg to c027.ogg)
    for (int i = 1; i <= 27; ++i) {
        char filename[64];
        snprintf(filename, sizeof(filename), "sounds/clav/c%03d.ogg", i);
        
        auto sample = std::make_unique<AudioSample>();
        if (loadSampleFromAsset(env, context, filename, sample)) {
            mClavSamples.push_back(std::move(sample));
        } else {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to load clav sample: %s", filename);
            return false;
        }
    }
    
    // Load swell samples (swell1.ogg to swell3.ogg)
    for (int i = 1; i <= 3; ++i) {
        char filename[64];
        snprintf(filename, sizeof(filename), "sounds/swells/swell%d.ogg", i);
        
        auto sample = std::make_unique<AudioSample>();
        if (loadSampleFromAsset(env, context, filename, sample)) {
            mSwellSamples.push_back(std::move(sample));
        } else {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to load swell sample: %s", filename);
            return false;
        }
    }
    
    __android_log_print(ANDROID_LOG_INFO, TAG, "Successfully loaded %zu celesta, %zu clav, and %zu swell samples",
                       mCelestaSamples.size(), mClavSamples.size(), mSwellSamples.size());
    return true;
}

bool SimpleOboePlayer::loadSampleFromAsset(JNIEnv* env, jobject context, const char* filename, std::unique_ptr<AudioSample>& sample) {
    // Get the AssetManager from the context
    jclass contextClass = env->GetObjectClass(context);
    jmethodID getAssetsMethod = env->GetMethodID(contextClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jobject assetManagerObj = env->CallObjectMethod(context, getAssetsMethod);
    
    AAssetManager* assetManager = AAssetManager_fromJava(env, assetManagerObj);
    if (!assetManager) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to get AssetManager");
        return false;
    }
    
    // Open the asset
    AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_STREAMING);
    if (!asset) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to open asset: %s", filename);
        return false;
    }
    
    // Set up the AssetData structure for libvorbisfile callbacks
    AssetData assetData;
    assetData.asset = asset;
    assetData.offset = 0;
    assetData.length = AAsset_getLength(asset);
    
    // Set up libvorbisfile callbacks
    ov_callbacks callbacks;
    callbacks.read_func = assetReadCallback;
    callbacks.seek_func = assetSeekCallback;
    callbacks.close_func = assetCloseCallback;
    callbacks.tell_func = assetTellCallback;
    
    // Open the OGG file using libvorbisfile
    OggVorbis_File vf;
    int result = ov_open_callbacks(&assetData, &vf, nullptr, 0, callbacks);
    if (result < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to open OGG file %s: error code %d", filename, result);
        AAsset_close(asset);
        return false;
    }
    
    // Get file info
    vorbis_info* info = ov_info(&vf, -1);
    if (!info) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to get OGG info for %s", filename);
        ov_clear(&vf);
        return false;
    }
    
    // Calculate total samples
    ogg_int64_t totalSamples = ov_pcm_total(&vf, -1);
    if (totalSamples <= 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Invalid sample count for %s", filename);
        ov_clear(&vf);
        return false;
    }
    
    // Prepare the AudioSample
    sample->sampleRate = info->rate;
    sample->channels = info->channels;
    sample->data.resize(totalSamples * info->channels);
    
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Loading %s: %lld samples, %d channels, %ld Hz", 
                       filename, totalSamples, info->channels, info->rate);
    
    // Read the audio data
    size_t samplesRead = 0;
    const int BUFFER_SIZE = 4096; // Read in chunks
    
    while (samplesRead < totalSamples * info->channels) {
        float** pcm;
        long samples = ov_read_float(&vf, &pcm, BUFFER_SIZE, nullptr);
        
        if (samples < 0) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Error reading OGG data from %s: %ld", filename, samples);
            ov_clear(&vf);
            return false;
        }
        if (samples == 0) {
            break; // End of file
        }
        
        // Interleave the channels if needed
        for (int i = 0; i < samples; ++i) {
            for (int c = 0; c < info->channels; ++c) {
                if (samplesRead + i * info->channels + c < sample->data.size()) {
                    sample->data[samplesRead + i * info->channels + c] = pcm[c][i];
                }
            }
        }
        
        samplesRead += samples * info->channels;
    }
    
    // Clean up
    ov_clear(&vf);
    
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Successfully loaded %s: %zu samples of audio data", 
                       filename, samplesRead);
    
    return true;
}

void SimpleOboePlayer::start() {
    if (mAudioStream) {
        oboe::Result result = mAudioStream->requestStart();
        if (result != oboe::Result::OK) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Failed to start stream: %s",
                                oboe::convertToText(result));
        }
    }
}

void SimpleOboePlayer::stop() {
    if (mAudioStream) {
        mAudioStream->requestStop();
        mAudioStream->close();
        mAudioStream.reset();
    }
}

int SimpleOboePlayer::calculateSampleIndex(int sizeBytes) {
    // Implement the exact Wikipedia pitch calculation algorithm
    double pitch = MAX_PITCH - std::min(MAX_PITCH, std::log(sizeBytes + LOG_USED) / std::log(LOG_USED));
    
    // Add fuzz factor (±2 random variation)
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    static thread_local std::uniform_int_distribution<> fuzzDist(-2, 2);
    
    int fuzz = fuzzDist(gen);
    double adjustedPitch = std::max(0.0, std::min(MAX_PITCH, pitch + fuzz));
    
    // Convert pitch (0-100) to sample index (0-26 for celesta/clav)
    int sampleIndex = static_cast<int>(std::floor(adjustedPitch * 26.0 / MAX_PITCH));
    return std::clamp(sampleIndex, 0, 26);
}

Voice* SimpleOboePlayer::findFreeVoice() {
    for (auto& voice : mVoices) {
        if (!voice->isActive) {
            return voice.get();
        }
    }
    
    // If all voices are busy, steal the one that's furthest along
    Voice* oldestVoice = mVoices[0].get();
    size_t maxPosition = oldestVoice->position;
    
    for (auto& voice : mVoices) {
        if (voice->position > maxPosition) {
            maxPosition = voice->position;
            oldestVoice = voice.get();
        }
    }
    
    return oldestVoice;
}

void SimpleOboePlayer::playWikipediaEdit(int sizeBytes, bool isAddition, float volume) {
    std::lock_guard<std::mutex> lock(mLock);
    
    if (sizeBytes <= 0) return;
    
    int sampleIndex = calculateSampleIndex(sizeBytes);
    AudioSample* selectedSample = nullptr;
    
    // Choose sample based on edit type
    if (isAddition && !mCelestaSamples.empty()) {
        // Additions: use celesta (brighter sound)
        if (sampleIndex < mCelestaSamples.size()) {
            selectedSample = mCelestaSamples[sampleIndex].get();
        }
    } else if (!mClavSamples.empty()) {
        // Deletions: use clav (darker sound)
        if (sampleIndex < mClavSamples.size()) {
            selectedSample = mClavSamples[sampleIndex].get();
        }
    }
    
    if (selectedSample) {
        Voice* voice = findFreeVoice();
        if (voice) {
            voice->trigger(selectedSample, std::clamp(volume, 0.0f, 1.0f));
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "Playing sound for %d bytes (%s, pitch index: %d)",
                               sizeBytes, isAddition ? "addition" : "deletion", sampleIndex);
        }
    }
    
    // Ensure stream is running
    if (mAudioStream && mAudioStream->getState() != oboe::StreamState::Started) {
        start();
    }
}

oboe::DataCallbackResult SimpleOboePlayer::onAudioReady(
        oboe::AudioStream *audioStream,
        void *audioData,
        int32_t numFrames
) {
    float *outputBuffer = static_cast<float *>(audioData);
    int32_t channelCount = audioStream->getChannelCount();
    
    std::lock_guard<std::mutex> lock(mLock);
    
    // Clear output buffer
    std::fill(outputBuffer, outputBuffer + numFrames * channelCount, 0.0f);
    
    // Mix all active voices
    for (auto& voice : mVoices) {
        if (voice->isActive) {
            for (int32_t i = 0; i < numFrames; ++i) {
                float sample = voice->getNextSample();
                if (sample != 0.0f) {
                    // Mix to both channels (stereo)
                    outputBuffer[i * channelCount] += sample;
                    if (channelCount > 1) {
                        outputBuffer[i * channelCount + 1] += sample;
                    }
                }
            }
        }
    }
    
    return oboe::DataCallbackResult::Continue;
}

void SimpleOboePlayer::onErrorAfterClose(
        oboe::AudioStream *audioStream,
        oboe::Result error
) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "Error after close: %s",
                        oboe::convertToText(error));
}