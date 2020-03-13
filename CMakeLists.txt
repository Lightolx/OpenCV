cmake_minimum_required(VERSION 3.12)
project(findContours)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cvBar cvBar.cpp)
target_link_libraries(cvBar ${OpenCV_LIBS})

add_executable(findContours FindContour.cpp)
target_link_libraries(findContours ${OpenCV_LIBS})

add_executable(floodfill FloodFill.cpp)
target_link_libraries(floodfill ${OpenCV_LIBS})

add_executable(HoughTransform HoughTransform.cpp)
target_link_libraries(HoughTransform ${OpenCV_LIBS})

add_executable(read_vedio ReadinVedio.cpp)
target_link_libraries(read_vedio ${OpenCV_LIBS})

add_executable(dilate_erode DilateAndErode.cpp)
target_link_libraries(dilate_erode ${OpenCV_LIBS})

add_executable(instruction Instruction.cpp)
target_link_libraries(instruction ${OpenCV_LIBS})

add_executable(round Round.cpp)
target_link_libraries(round ${OpenCV_LIBS})