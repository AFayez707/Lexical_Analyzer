cmake_minimum_required(VERSION 3.8)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp graph/Edge.cpp graph/Edge.h graph/State.cpp graph/State.h graph/Graph.cpp graph/Graph.h
        DFA_Generator/DFA_Generator.h regex-to-nfa/construct_nfa.cpp regex-to-nfa/nfa.cpp regex-to-nfa/nfa.h
        regex-to-nfa/NFAState.cpp regex-to-nfa/NFAState.h regex-to-nfa/IDGenerator.cpp regex-to-nfa/IDGenerator.h
        dfa_reduction/DFA_Reducer.cpp dfa_reduction/DFA_Reducer.h test/main.cpp)
add_executable(lexical_analyzer ${SOURCE_FILES})
