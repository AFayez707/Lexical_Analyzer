//
// Created by ahmed on 12/5/17.
//

#include <stack>
#include <iomanip>
#include "Parser.h"
#include "grammar_reader/CFG_Reader.h"
#include "first_follow/First.h"
#include "first_follow/Follow.h"
#include "grammar_reader/Left_Recursion.h"

Parser::Parser(string file_path, const string &log_file, queue<string> tokens) {
    this->file_path = move(file_path);
    this->logger = new ofstream(log_file, ios_base::out);
    this->tokens = move(tokens);

    __init();
}

Parser::Parser(string start_symbol, Parse_Table *parse_table, queue<string> tokens, const string &log_file) {
    this->start_symbol = move(start_symbol);
    this->parse_table = parse_table;
    this->tokens = move(tokens);
    this->logger = new ofstream(log_file, ios_base::app);
}

void Parser::parse() {
    fprintf(stdout, "\n\nParsing..\n\n");
    *this->logger << "\n\nParsing..\n\n";

    stack<string> parse_stack;
    parse_stack.push(DOLLAR_SIGN);
    parse_stack.push(this->start_symbol);

    while (true) {
        string top = parse_stack.top();
        string input = this->tokens.front();

        // is empty
        if (top == input && top == DOLLAR_SIGN) break;

        // found a match, pop from stack & input
        if (top == input) {
            fprintf(stdout, "  Matched: %s\n", top.c_str());
            *this->logger << "  Matched: " << top << endl;
            parse_stack.pop();
            this->tokens.pop();
            continue;
        }

        // non-terminal
        vector<string> production = this->parse_table->peek(top, input);

//        if(top == "EXPRESSION" && input == "id"){
//            production.pop_back();
//            production.pop_back();
//        }

        if (production.empty() || production[0] == ERROR) {
            // if all of the input is consumed
            if (input == DOLLAR_SIGN) {
                fprintf(stdout, "  Syntax Error, missing: %s", top.c_str());
                *this->logger << "  Syntax Error, missing: " << top;
                parse_stack.pop();
            } else {
                fprintf(stdout, "  Syntax Error, unexpected token: %s", input.c_str());
                *this->logger << "  Syntax Error, unexpected token: " << input;
                this->tokens.pop();
            }
        } else if (production[0] == SYNC) {
            fprintf(stdout, "  Sync => pop: %s", top.c_str());
            *this->logger << "  Sync => pop: " << top;
            parse_stack.pop();
        } else if (production[0] == EPS) {
            fprintf(stdout, "  Epsilon => pop");
            *this->logger << "  Epsilon => pop";
            parse_stack.pop();
        } else {
            parse_stack.pop();
            fprintf(stdout, "  %s -> ", top.c_str());
            *this->logger << "  " << top << " -> ";
            for (int i = (int) production.size() - 1; i > -1; i--)
                parse_stack.push(production[i]);

            for (const string &str : production) {
                fprintf(stdout, "%s ", str.c_str());
                *this->logger << str << " ";
            }
        }
        fprintf(stdout, "\n");
        *this->logger << endl;
    }
    // Close log file buffer
    this->logger->close();
}

void Parser::__init() {
    *this->logger << left;

    FIRST_FOLLOW first, follow;
    GRAMMAR grammar;
    string start_symbol;
    set<string> terminals;
    map<string, int> order;
    vector<string> ordered_grammar_vector;

    /**
     * Reading grammar file
     */
    CFG_Reader cfg_reader(this->file_path);
    start_symbol = cfg_reader.get_start_symbol();
    this->start_symbol = start_symbol; // set start symbol
    terminals = cfg_reader.get_terminals();
    grammar = cfg_reader.get_grammar();
    order = cfg_reader.get_order();
    ordered_grammar_vector = cfg_reader.get_grammar_in_order();
    cfg_reader.log(this->logger);


    // Eliminating Ambiguity
    Left_Recursion left_recursion(grammar, order, terminals, ordered_grammar_vector);
    grammar = left_recursion.get();
    left_recursion.log(this->logger);

    /**
     * Generating First
     */
    First first_gen(grammar, terminals);
    first = first_gen.get();
    first_gen.log(this->logger);

    /**
     * Generating Follow
     */
    Follow follow_gen(start_symbol, grammar, terminals, first);
    follow = follow_gen.get();
    follow_gen.log(this->logger);

    /**
     * Forming the parse table
     */
    this->parse_table = new Parse_Table(first, follow, grammar, terminals);
    this->parse_table->log(this->logger);
}
