cmake_minimum_required(VERSION 3.9)
project(parser_generator)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(parser_generator test/main.cpp parser-generator/parse_table/Parse_Table.cpp
        parser-generator/parse_table/Parse_Table.h
        parser-generator/parser/Parser.cpp parser-generator/parser/Parser.h
        parser-generator/grammar_reader/CFG_Reader.cpp parser-generator/grammar_reader/CFG_Reader.h
        test/test_parse_table.h test/test_input_reader.h
        parser-generator/first_follow/First.cpp parser-generator/first_follow/First.h parser-generator/first_follow/Follow.cpp parser-generator/first_follow/Follow.h parser-generator/grammar_reader/Left_Recursion.cpp parser-generator/grammar_reader/Left_Recursion.h)
