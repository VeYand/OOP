cmake_minimum_required(VERSION 3.26)
project(FindMaxEx)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
        main.cpp
        include/FindMaxEx.h
        include/Athlete.h
)

add_executable(${PROJECT_NAME}Test
        test/FindMaxExTest.cpp
        include/FindMaxEx.h
        include/Athlete.h
)

target_link_libraries(${PROJECT_NAME}Test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)

