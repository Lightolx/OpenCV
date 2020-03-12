cmake_minimum_required(VERSION 3.12)
project(findContours)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cvBar cvBar.cpp)
target_link_libraries(cvBar ${OpenCV_LIBS})

add_executable(findContours FindContour.cpp)
target_link_libraries(findContours ${OpenCV_LIBS})