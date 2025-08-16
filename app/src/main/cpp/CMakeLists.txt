cmake_minimum_required(VERSION 3.22.1)

project(oboe_audio_player)

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

find_package(oboe REQUIRED CONFIG)
find_package(vorbis REQUIRED CONFIG)
find_package(ogg REQUIRED CONFIG)

add_library(oboe_audio_player SHARED native-lib.cpp SimpleOboePlayer.cpp)

target_link_libraries(oboe_audio_player
        PRIVATE
        android
        log
        oboe::oboe
        vorbis::vorbis
        vorbis::vorbisfile
	ogg::ogg
)
