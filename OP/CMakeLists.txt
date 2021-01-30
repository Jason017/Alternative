cmake_minimum_required(VERSION 3.17)
project(OOP)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV 4.3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(OOP main.cpp TargetDetector.cpp TargetDetector.h DataCollector.h)
target_link_libraries(OOP ${OpenCV_LIBS})