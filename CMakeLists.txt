cmake_minimum_required(VERSION 3.5)
project(VideoDeghosting)

find_package(OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Deghosting.cpp Deghosting.h Video.cpp Video.h)
add_executable(VideoDeghosting ${SOURCE_FILES})

target_link_libraries( VideoDeghosting ${OpenCV_LIBS} )