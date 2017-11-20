cmake_minimum_required(VERSION 3.8)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test/main.cpp graph/State.h graph/State.cpp graph/Graph.h graph/Graph.cpp
        regex-to-nfa/construct_NFA.cpp regex-to-nfa/NFA.cpp regex-to-nfa/NFA.h
        dfa_reduction/DFA_Reducer.cpp dfa_reduction/DFA_Reducer.h
        dfa_generator/DFA_Generator.cpp dfa_generator/DFA_Generator.h)

# Add ability to read file from project dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(lexical_analyzer ${SOURCE_FILES})
