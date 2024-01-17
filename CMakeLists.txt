cmake_minimum_required(VERSION 3.12)
project(VideoInformation)

set(CMAKE_CXX_STANDARD 11)

set(OpenCV_DIR "D:/OpenCV/opencv/build")

find_package(OpenCV REQUIRED)

add_executable(VideoInformation main.cpp)

target_include_directories(VideoInformation PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(VideoInformation ${OpenCV_LIBS})
