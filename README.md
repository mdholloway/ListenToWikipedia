# Listen To Wikipedia - Android

A native Android adaptation of the original [Listen To Wikipedia](http://listen.hatnote.com) web application, which provides real-time audio-visual representations of Wikipedia edits as they happen around the world.

## About

This project brings the mesmerizing experience of "listening" to Wikipedia edits to Android devices. Each edit generates a unique sound, creating an ambient soundscape that reflects the pulse of knowledge creation.

Originally created as a web application by Stephen LaPorte and Mahmoud Hashemi, this Android version was built to explore contemporary Android development practices and dive deep into native audio programming with the Android NDK.

## Features

- **Real-time Wikipedia monitoring**: Connects to Wikimedia's Server-Sent Events stream for live edit notifications
- **Audio synthesis**: Custom Faust-based DSP for generating sounds corresponding to Wikipedia edit diff sizes 
- **Modern Android UI**: Built with Jetpack Compose for a responsive, material design interface
- **Native audio processing**: Low-latency audio using Google's Oboe library and custom NDK implementation

## Technical Architecture

### Core Technologies

- **Language**: Kotlin with modern Android idioms
- **UI Framework**: Jetpack Compose with Material 3 design
- **Audio Engine**: 
  - [Faust](https://faust.grame.fr/) DSP language for audio synthesis
  - [Google Oboe](https://github.com/google/oboe) for low-latency audio
- **Networking**: Ktor client with SSE (Server-Sent Events) support
- **Architecture**: MVVM pattern with LiveData and ViewModels

### Audio Processing Chain
   ```
   Wikipedia Event → Kotlin Logic → JNI → Faust DSP → Oboe → Audio Hardware
   ```

### Dependencies

- **Android**: API 24+ (Android 7.0), targeting API 36
- **Jetpack Compose**: Latest stable BOM (2025.07.00)
- **Ktor**: 3.2.2 for HTTP client and SSE support
- **Oboe**: 1.9.3 for high-performance audio
- **Kotlin Serialization**: For JSON parsing of Wikipedia events

## Build Requirements

- Android Studio with NDK support
- CMake 3.22.1+
- Android NDK with C++17 support
- Faust compiler (for modifying DSP code)

## What Makes This Interesting

### For Android Developers
- **Modern Android practices**: Showcases Jetpack Compose, ViewModels, and Kotlin coroutines
- **NDK integration**: Real-world example of JNI bindings and native library integration
- **Audio programming**: Professional audio development with Oboe and low-latency considerations
- **Real-time data**: SSE implementation for live streaming data

### For Audio Developers
- **Faust integration**: Complete example of embedding Faust DSP in Android
- **Polyphonic synthesis**: Multi-voice audio generation with parameter control
- **Mobile audio constraints**: Handling Android's audio latency and buffer management

## Permissions

The app requests `RECORD_AUDIO` permission, which is required by the audio system even though the app only produces sound (Android audio library requirement).

## Future Enhancements

- Support for different Wikipedia language editions
- Custom instrument selection
- User-configurable sound parameters
