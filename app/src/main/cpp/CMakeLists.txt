cmake_minimum_required(VERSION 3.22.1)

project(ListenToWikipedia)

add_library(dsp_faust SHARED java_interface_wrap.cpp DspFaust.cpp)

find_library(log-lib log)
find_library(opensles-lib OpenSLES)

find_package(oboe REQUIRED CONFIG)

target_link_options(dsp_faust PUBLIC -Wl,-z,max-page-size=16384)
target_link_libraries(dsp_faust oboe::oboe ${log-lib} ${opensles-lib})