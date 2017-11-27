cmake_minimum_required(VERSION 3.2)
project(Steiner)

set(CMAKE_CXX_STANDARD 11)

install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/project  DESTINATION include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/project/)

set(SOURCE_FILES project/main.cpp project/objects.h project/construction_tools.h)
add_executable(Steiner ${SOURCE_FILES})
