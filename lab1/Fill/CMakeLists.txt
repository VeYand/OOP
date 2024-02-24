cmake_minimum_required(VERSION 3.26)
project(Fill)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/test)

add_executable(Fill
        main.cpp
        include/MapUtilities.h
        src/MapUtilities.cpp
        src/MapUtilities.cpp)
