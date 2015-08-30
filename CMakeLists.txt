cmake_minimum_required(VERSION 3.3)
project(EmulatorCore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CoreEmulator.cpp CoreEmulator.h Processor/CPU.cpp Processor/CPU.h Memory/MemoryMap.cpp Memory/MemoryMap.h Memory/Controllers/MemoryController.h Common.h)
add_executable(EmulatorCore ${SOURCE_FILES})