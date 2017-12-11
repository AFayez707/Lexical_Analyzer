//
// Created by ahmed on 12/5/17.
//

#ifndef PARSER_GENERATOR_PARSER_H
#define PARSER_GENERATOR_PARSER_H


#include <queue>
#include "parse_table/Parse_Table.h"

class Parser {
public:
    Parser(string file_path, const string &log_file, queue<string> tokens);

    // Constructor just for testing
    Parser(string start_symbol, Parse_Table *parse_table, queue<string> tokens, const string &log_file);

    void parse();

private:
    string file_path;
    ofstream *logger;
    string start_symbol;
    queue<string> tokens;
    Parse_Table *parse_table;

    void __init();
};


#endif //PARSER_GENERATOR_PARSER_H
