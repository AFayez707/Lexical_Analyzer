cmake_minimum_required(VERSION 3.9)
project(parser_generator)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(parser_generator test/main.cpp parser/parse_table/Parse_Table.cpp parser/parse_table/Parse_Table.h
        parser/Parser.cpp parser/Parser.h parser/grammar_reader/CFG_Reader.cpp parser/grammar_reader/CFG_Reader.h
        test/test_parse_table.h test/test_input_reader.h test/test_parser.h parser/first_follow/First.cpp
        parser/first_follow/First.h parser/first_follow/Follow.cpp parser/first_follow/Follow.h
        parser/grammar_reader/Left_Recursion.cpp parser/grammar_reader/Left_Recursion.h)
