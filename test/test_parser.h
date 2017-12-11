//
// Created by ahmed on 12/11/17.
//

#ifndef PARSER_GENERATOR_TEST_PARSING_H
#define PARSER_GENERATOR_TEST_PARSING_H

#include "../parser/Parser.h"

void run_test_parser(Parse_Table *parse_table);

void run_test_parser(Parse_Table *parse_table) {
    queue <string> q;

    q.push("(");
    q.push("id");
    q.push("+");
    q.push("(");
    q.push("*");
    q.push("id");
    q.push(")");
    q.push(DOLLAR_SIGN);

    Parser parser("E", parse_table, q, "parser-log.txt");

    parser.parse();
}

#endif //PARSER_GENERATOR_TEST_PARSING_H
