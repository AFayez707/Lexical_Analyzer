//
// Created by ahmed on 12/5/17.
//

#include "Parser.h"
#include "../grammar_reader/CFG_Reader.h"
#include "../first_follow/First.h"
#include "../first_follow/Follow.h"
#include "../grammar_reader/Left_Recursion.h"

Parser::Parser(string file_path, const string &log_file, queue<string> tokens) {
    this->file_path = move(file_path);
    this->logger = new ofstream(log_file, ios_base::out);
    this->tokens = move(tokens);

    __init();
}

void Parser::parse() {

    // Close log file buffer
    this->logger->close();
}

void Parser::__init() {
    FIRST_FOLLOW first, follow;
    GRAMMAR grammar;
    string start_symbol;
    set<string> terminals;

    // Reading grammar file
    CFG_Reader cfg_reader(this->file_path);
    start_symbol = cfg_reader.get_start_symbol();
    terminals = cfg_reader.get_terminals();
    grammar = cfg_reader.get_grammar();

    // Eliminating Ambiguity
    Left_Recursion left_recursion(start_symbol, grammar);
    grammar = left_recursion.get();
    left_recursion.log(this->logger);

    // Generating First
    First first_gen(start_symbol, grammar);
    first = first_gen.get();
    first_gen.log(this->logger);

    // Generating Follow
    Follow follow_gen(start_symbol, grammar);
    follow = follow_gen.get();
    follow_gen.log(this->logger);

    // Forming the parse table
    this->parse_table = new Parse_Table(first, follow, grammar, terminals);
}
