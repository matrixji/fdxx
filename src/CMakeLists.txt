cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(fdxx)

set(fdxx_sources
    src/DefaultRunloop.cpp
    src/RunloopFactory.cpp
    src/LinuxEpoll.cpp
    src/DefaultLogger.cpp
    )

include_directories(
    include
)

add_library(fdxx_static STATIC ${fdxx_sources})
add_library(fdxx_shared SHARED ${fdxx_sources})

set_target_properties(fdxx_static PROPERTIES OUTPUT_NAME "fdxx")
set_target_properties(fdxx_shared PROPERTIES OUTPUT_NAME "fdxx")
set_target_properties(fdxx_shared PROPERTIES VERSION 1.0 SOVERSION 1)


add_subdirectory(example)
