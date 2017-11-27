cmake_minimum_required(VERSION 3.2)
project(Steiner)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp objects.h construction_tools.h)
add_executable(Steiner ${SOURCE_FILES})
