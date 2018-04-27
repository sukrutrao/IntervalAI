cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(IntervalAI)

set(IntervalAI_VERSION_MAJOR 0)
set(IntervalAI_VERSION_MINOR 0)

include_directories(include)
include_directories(cbmc/src)

file(GLOB SOURCES "src/*.cpp")

add_executable(IntervalAI ${SOURCES})