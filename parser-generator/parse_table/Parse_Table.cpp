//
// Created by ahmed on 12/5/17.
//

#include "Parse_Table.h"

Parse_Table::Parse_Table(MSS first, MSS follow, MSV grammar, set<string> terminals) {
    this->first = move(first);
    this->follow = move(follow);
    this->grammar = move(grammar);
    this->terminals = move(terminals);

    this->__sync_and_error();
    this->__build_parse_table();
}

vector<string> Parse_Table::peek(const string &stack_top, const string &token) {
    return this->parse_table[stack_top][token];
}

void print_separator(unsigned long terminals_cnt) {
    string str;
    for (unsigned int i = 0; i < (terminals_cnt + 1) * 18; i++)
        str += "-";

    printf("%s\n", str.c_str());
}

void Parse_Table::display() {
    print_separator(terminals.size());
    fprintf(stdout, "                 |");
    for (auto &T: this->terminals)
        fprintf(stdout, " %-15s |", T.c_str());

    printf("\n");
    print_separator(terminals.size());

    for (auto &non_T: this->parse_table) {
        fprintf(stdout, " %-15s |", non_T.first.c_str());
        for (auto &T: this->terminals) {
            string str;
            for (auto &to: this->parse_table[non_T.first][T])
                str += to;

            fprintf(stdout, " %-15s |", str.c_str());
        }
        fprintf(stdout, "\n");
    }

    print_separator(terminals.size());
}

void Parse_Table::__sync_and_error() {
    for (auto &rule:this->grammar) {
        string LHS = rule.first;
        set<string> LHS_follow = this->follow[LHS];
        for (const string &terminal: this->terminals) {
            if (LHS_follow.find(terminal) != LHS_follow.end())
                this->parse_table[LHS][terminal] = {SYNC};
            else
                this->parse_table[LHS][terminal] = {ERROR};
        }
    }
}

void Parse_Table::__build_parse_table() {
    // for each production rule
    for (auto &rule:this->grammar) {
        string LHS = rule.first;

        // loop RHS products separated by OR
        for (auto &RHS: rule.second) {
            bool eps_in_first_RHS = false;

            // loop all the first of RHS
            for (const string &terminal: this->first[RHS[0]]) {
                this->parse_table[LHS][terminal] = RHS;

                if (terminal == EPS)
                    eps_in_first_RHS = true;
            }

            bool eps_in_follow_LHS = false;

            // loop all follow of LHS
            if (eps_in_first_RHS) {
                for (const string &terminal: this->follow[LHS]) {
                    this->parse_table[LHS][terminal] = RHS;

                    if (terminal == EPS)
                        eps_in_follow_LHS = true;
                }
            }

            if (eps_in_follow_LHS)
                this->parse_table[LHS][DOLLAR_SIGN] = RHS;
        }
    }
}
