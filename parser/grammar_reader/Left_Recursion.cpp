//
// Created by ahmed on 12/11/17.
//

#include <iomanip>
#include "Left_Recursion.h"

Left_Recursion::Left_Recursion(string start_symbol, GRAMMAR grammar) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);

    __eliminate();
}

GRAMMAR Left_Recursion::get() {
    return this->ambiguity_free_grammar;
}

void Left_Recursion::log(ofstream *log_file) {
    *log_file << "\n\nAmbiguity free grammar:\n";
    for (auto &rule: this->ambiguity_free_grammar) {
        *log_file << "    # " << setw(18) << rule.first << "➜ ";
        for (int i = 0; i < rule.second.size(); i++) {
            for (const string &j : rule.second[i]) {
                *log_file << j << " ";
            }
            *log_file << (i < rule.second.size() - 1 ? "| " : "");
        }
        *log_file << endl;
    }
    log_file->flush();
}

void Left_Recursion::__eliminate() {
    // TODO
    // just passing the grammar as it came here
    this->ambiguity_free_grammar = this->grammar;
}
