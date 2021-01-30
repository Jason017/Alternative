cmake_minimum_required(VERSION 3.17)
project(contour)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV 4.3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(contour main.cpp)
target_link_libraries(contour ${OpenCV_LIBS})