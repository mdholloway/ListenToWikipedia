cmake_minimum_required(VERSION 3.22.1)

project("oboe_audio_player")

add_library(oboe_audio_player SHARED native-lib.cpp SimpleOboePlayer.cpp)

find_library(log-lib log)

find_package(oboe REQUIRED CONFIG)

target_link_libraries(oboe_audio_player android oboe::oboe ${log-lib})