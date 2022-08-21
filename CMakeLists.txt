cmake_minimum_required(VERSION 3.23)
project(ezlang)

set(CMAKE_C_STANDARD 99)

add_subdirectory(ezc)
include_directories(ezc/include)

add_executable(ezlang src/main.cpp)

target_link_libraries(ezlang ezc)