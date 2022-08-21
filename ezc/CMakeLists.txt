cmake_minimum_required(VERSION 3.23)
project(ezc)

set(CMAKE_C_STANDARD 99)

include_directories(include)
set(SOURCES src/lexer/lexer.cpp src/ez.cpp)

add_library(ezc SHARED ${SOURCES})