cmake_minimum_required(VERSION 3.26)
project(Invert)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/test)

add_executable(Invert
        main.cpp
        src/MatrixOperations.cpp
        include/MatrixOperations.h)
