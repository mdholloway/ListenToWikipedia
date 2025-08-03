cmake_minimum_required(VERSION 3.22.1)

project("oboe_audio_player")

add_library(
        oboe_audio_player
        SHARED
        native-lib.cpp
        synth.cpp
        StandardBell.cpp
        OboeAudioPlayer.cpp
)

find_library(log-lib log)

find_package(oboe REQUIRED CONFIG)

add_subdirectory(third_party/faust)

target_link_libraries(
        oboe_audio_player PRIVATE FaustHeaders
        android
        oboe::oboe
        ${log-lib}
)

target_link_options(
        oboe_audio_player
        PRIVATE
        -Wl,-z,max-page-size=16384
        -Wl,-z,common-page-size=16384
)