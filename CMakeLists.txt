cmake_minimum_required(VERSION 2.6)
project(IntervalAI)

set(IntervalAI_VERSION_MAJOR 0)
set(IntervalAI_VERSION_MINOR 0)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(IntervalAI ${SOURCES})
