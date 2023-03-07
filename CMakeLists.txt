cmake_minimum_required(VERSION 3.17.3)

project(Sniffy VERSION 1.0)

add_executable(Sniffy main.cpp Function.cpp Function.h Detector.cpp Detector.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall)
