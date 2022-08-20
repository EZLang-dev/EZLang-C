cmake_minimum_required(VERSION 3.23)
project(ezc C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
set(SOURCES src/ez.c)

add_library(ezc SHARED ${SOURCES})
