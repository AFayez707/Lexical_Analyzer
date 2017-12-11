//
// Created by ahmed on 12/11/17.
//

#include <fstream>
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

}

void First::__generate() {
    // TODO
}
