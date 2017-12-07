cmake_minimum_required(VERSION 3.9)
project(parser_generator)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(parser_generator test/main.cpp parser-generator/parse_table/Parse_Table.cpp
        parser-generator/parse_table/Parse_Table.h
        parser-generator/parser/Parser.cpp parser-generator/parser/Parser.h
        parser-generator/grammar_reader/Input_Reader.cpp parser-generator/grammar_reader/Input_Reader.h test/test_parse_table.h)
