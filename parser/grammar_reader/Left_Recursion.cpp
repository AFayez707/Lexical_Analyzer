//
// Created by ahmed on 12/11/17.
//

#include "Left_Recursion.h"

Left_Recursion::Left_Recursion(string start_symbol, GRAMMAR grammar) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);

    __eliminate();
}

GRAMMAR Left_Recursion::get() {
    return this->non_ambiguous_grammar;
}

void Left_Recursion::log(ofstream *log_file) {

}

void Left_Recursion::__eliminate() {
    // TODO
}
