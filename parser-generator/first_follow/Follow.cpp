//
// Created by ahmed on 12/11/17.
//

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

}

void Follow::__generate() {
    // TODO
}
