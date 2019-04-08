cmake_minimum_required(VERSION 3.0)

set(example_sources
    example.cpp
)

#include_directories(
#    include
#)

add_executable(fdxx_example ${example_sources})
target_link_libraries(fdxx_example fdxx_static pthread)
