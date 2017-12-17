//
// Created by ahmed on 12/11/17.
//

#include <fstream>
#include <iomanip>
#include "First.h"

First::First(string start_symbol, GRAMMAR grammar) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);

    __generate();
}

FIRST_FOLLOW First::get() {
    return this->first;
}

void First::log(ofstream *log_file) {
    *log_file << "\n\nFirst:\n";
    for (pair<string, set<string>> entry: this->first) {
        *log_file << "  " << setw(18) << entry.first << " => ";
        for (const string &str: entry.second) {
            *log_file << str << ", ";
        }
        *log_file << endl;
    }
    log_file->flush();
}

void First::__generate() {
    // TODO
}
