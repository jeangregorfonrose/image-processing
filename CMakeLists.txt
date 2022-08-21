cmake_minimum_required(VERSION 3.20)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ImageProcessing main.cpp src/Image.cpp src/Image.h)
