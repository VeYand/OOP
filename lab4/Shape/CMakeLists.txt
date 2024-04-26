cmake_minimum_required(VERSION 3.26)
project(Shape)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.x
)

FetchContent_MakeAvailable(sfml)

add_executable(${PROJECT_NAME}
        main.cpp
        include/CPoint.h
        include/ISolidShape.h
        include/CLineSegment.h
        include/CTriangle.h
        include/CRectangle.h
        include/CCircle.h
        src/CLineSegment.cpp
        src/CTriangle.cpp
        src/CTriangle.cpp
        src/CRectangle.cpp
        src/CCircle.cpp
        include/ShapeControlService.h
        src/ShapeControlService.cpp
        src/ShapeControlService.cpp
        src/ShapeFactory.cpp
        include/ShapeFactory.h
        include/ICanvasDrawable.h
        include/ICanvasDrawable.h
        include/ICanvas.h
        include/ICanvas.h
        src/CCanvas.cpp
        include/CCanvas.h
        include/CCanvas.h
        include/CCanvas.h
        src/CCanvas.cpp
        src/CanvasWindowControlService.cpp
        include/CanvasWindowControlService.h
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

add_executable(${PROJECT_NAME}Test
        test/main.cpp
        test/CRectangleTest.cpp
        test/CTriangleTest.cpp
        test/CCircleTest.cpp
        test/CLineSegmentTest.cpp
        include/CPoint.h
        include/ISolidShape.h
        include/CLineSegment.h
        include/CTriangle.h
        include/CRectangle.h
        include/CCircle.h
        src/CLineSegment.cpp
        src/CTriangle.cpp
        src/CTriangle.cpp
        src/CRectangle.cpp
        src/CCircle.cpp
        src/ShapeFactory.cpp
        include/ShapeFactory.h
        src/ShapeFactory.cpp
        test/ShapeFactoryTest.cpp
        include/ICanvasDrawable.h
)

target_link_libraries(${PROJECT_NAME}Test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)

