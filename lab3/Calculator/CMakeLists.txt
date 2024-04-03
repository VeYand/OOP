cmake_minimum_required(VERSION 3.26)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

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
        src/Calculator.cpp
        include/Calculator.h
        src/Variable.cpp
        include/Variable.h
        src/Function.cpp
        include/Function.h
        src/CalculatorHandler.cpp
        include/CalculatorHandler.h
)

add_executable(${PROJECT_NAME}Test
        test/CalculatorTest.cpp
        src/Calculator.cpp
        include/Calculator.h
        src/Variable.cpp
        include/Variable.h
        src/Function.cpp
        include/Function.h
        src/CalculatorHandler.cpp
        include/CalculatorHandler.h
)

target_link_libraries(${PROJECT_NAME}Test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)

