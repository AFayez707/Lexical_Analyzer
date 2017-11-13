cmake_minimum_required(VERSION 3.8)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp graph/Edge.cpp graph/Edge.h graph/State.cpp graph/State.h graph/Graph.cpp graph/Graph.h)
add_executable(lexical_analyzer ${SOURCE_FILES})
