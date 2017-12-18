//
// Created by ahmed on 12/5/17.
//

#include "Parse_Table.h"
#include <iomanip>

Parse_Table::Parse_Table(FIRST_FOLLOW first, FIRST_FOLLOW follow, GRAMMAR grammar, set<string> terminals) {
    this->first = move(first);
    this->follow = move(follow);
    this->grammar = move(grammar);
    this->terminals = move(terminals);

    this->__sync_and_error();
    this->__build_parse_table();
}

vector<string> Parse_Table::peek(const string &non_terminal, const string &token) {
    return this->parse_table[non_terminal][token];
}

void Parse_Table::log(ofstream *log_file) {
    *log_file << left << "\n\nParse Table:\n------------\n";
    for (auto &non_terminal: this->parse_table) {
        *log_file << "    " << non_terminal.first << ":\n";
        for (const string &terminal: this->terminals) {
            *log_file << "        " << non_terminal.first << "  +  " << setw(10) << terminal << "  ➜  ";
            vector<string> production = this->peek(non_terminal.first, terminal);
            for (const string &i : production)
                *log_file << i << " ";
            *log_file << endl;
        }
        *log_file << endl;
    }
    log_file->flush();
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
        for (vector<string> &RHS: rule.second) {
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
