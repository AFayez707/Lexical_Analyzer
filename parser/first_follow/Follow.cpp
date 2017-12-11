//
// Created by ahmed on 12/11/17.
//

#include <iomanip>
#include "Follow.h"

Follow::Follow(string start_symbol, GRAMMAR grammar) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);

    __generate();
}

FIRST_FOLLOW Follow::get() {
    return this->follow;
}

void Follow::log(ofstream *log_file) {
    *log_file << "\n\nFollow:\n";
    for (pair<string, set<string>> entry: this->follow) {
        *log_file << "  " << setw(18) << entry.first << " => ";
        for (const string &str: entry.second) {
            *log_file << str << ", ";
        }
        *log_file << endl;
    }
}

void Follow::__generate() {
    // TODO
}
