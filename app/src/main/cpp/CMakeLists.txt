cmake_minimum_required(VERSION 3.22.1)

add_library(dsp_faust SHARED java_interface_wrap.cpp DspFaust.cpp)

find_library(log-lib log)

find_package(oboe REQUIRED CONFIG)

target_link_libraries(dsp_faust oboe::oboe ${log-lib})