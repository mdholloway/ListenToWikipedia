cmake_minimum_required(VERSION 3.22.1)

project(ListenToWikipedia)

add_library(dsp_faust SHARED java_interface_wrap.cpp DspFaust.cpp)

# Size optimization flags for release builds
target_compile_options(dsp_faust PRIVATE
    $<$<CONFIG:Release>:-Os>              # Optimize for size
    $<$<CONFIG:Release>:-ffunction-sections>
    $<$<CONFIG:Release>:-fdata-sections>
    $<$<CONFIG:Release>:-ffast-math>      # Aggressive math optimizations for DSP
    $<$<CONFIG:Release>:-fno-rtti>        # Disable RTTI if not needed
)

find_library(log-lib log)
find_library(opensles-lib OpenSLES)

find_package(oboe REQUIRED CONFIG)

target_link_options(dsp_faust PUBLIC 
    -Wl,-z,max-page-size=16384
    $<$<CONFIG:Release>:-Wl,--gc-sections>    # Remove unused sections
    $<$<CONFIG:Release>:-Wl,--strip-all>      # Strip all symbols
)
target_link_libraries(dsp_faust oboe::oboe ${log-lib} ${opensles-lib})
