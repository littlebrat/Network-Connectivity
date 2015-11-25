cmake_minimum_required(VERSION 3.3)
project(Network-Connectivity)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES)

add_executable(Network-Connectivity ${SOURCE_FILES} src/main.cpp)
add_executable(Test ${SOURCE_FILES} tests/main.cpp )