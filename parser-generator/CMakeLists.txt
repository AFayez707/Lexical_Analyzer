cmake_minimum_required(VERSION 3.9)
project(parser_generator)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(parser_generator test/main.cpp)
