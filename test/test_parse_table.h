//
// Created by ahmed on 12/8/17.
//

#ifndef PARSER_GENERATOR_TEST_PARSE_TABLE_H
#define PARSER_GENERATOR_TEST_PARSE_TABLE_H

#include "../parser-generator/parse_table/Parse_Table.h"

void run_parse_table_test();

void run_parse_table_test() {
    MSS first, follow;
    MSV grammar;

    first["E"].insert("(");
    first["E"].insert("id");

    first["E^"].insert("+");
    first["E^"].insert(EPS);

    first["T"].insert("(");
    first["T"].insert("id");

    first["T^"].insert("*");
    first["T^"].insert(EPS);

    first["F"].insert("(");
    first["F"].insert("id");

    first["("].insert("(");
    first[")"].insert(")");
    first["+"].insert("+");
    first["*"].insert("*");
    first["id"].insert("id");
    first[EPS].insert(EPS);

    /**
     *
     */
    follow["E"].insert(")");
    follow["E"].insert(DOLLAR_SIGN);

    follow["E^"].insert(")");
    follow["E^"].insert(DOLLAR_SIGN);

    follow["T"].insert("+");
    follow["T"].insert(")");
    follow["T"].insert(DOLLAR_SIGN);

    follow["T^"].insert("+");
    follow["T^"].insert(")");
    follow["T^"].insert(DOLLAR_SIGN);

    follow["F"].insert("*");
    follow["F"].insert("+");
    follow["F"].insert(")");
    follow["F"].insert(DOLLAR_SIGN);

    /**
     *
     */
    vector<string> v;
    v.emplace_back("T");
    v.emplace_back("E^");
    grammar["E"].emplace_back(v);

    v.clear();
    v.emplace_back("+");
    v.emplace_back("T");
    v.emplace_back("E^");
    grammar["E^"].emplace_back(v);

    v.clear();
    v.emplace_back(EPS);
    grammar["E^"].emplace_back(v);

    v.clear();
    v.emplace_back("F");
    v.emplace_back("T^");
    grammar["T"].emplace_back(v);

    v.clear();
    v.emplace_back("*");
    v.emplace_back("F");
    v.emplace_back("T^");
    grammar["T^"].emplace_back(v);

    v.clear();
    v.emplace_back(EPS);
    grammar["T^"].emplace_back(v);

    v.clear();
    v.emplace_back("id");
    grammar["F"].emplace_back(v);

    v.clear();
    v.emplace_back("(");
    v.emplace_back("E");
    v.emplace_back(")");
    grammar["F"].emplace_back(v);

    /**
     *
     */
    set<string> terminals;
    terminals.insert("+");
    terminals.insert("*");
    terminals.insert("(");
    terminals.insert(")");
    terminals.insert("id");
    terminals.insert(EPS);
    terminals.insert(DOLLAR_SIGN);

    Parse_Table *tg = new Parse_Table(first, follow, grammar, terminals);
    tg->display_parse_table();
}

#endif //PARSER_GENERATOR_TEST_PARSE_TABLE_H
