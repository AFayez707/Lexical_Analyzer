//
// Created by ahmed on 12/5/17.
//

#include "Input_Reader.h"

Input_Reader::Input_Reader(string file_path) {
    this->file_path = move(file_path);
    read_file(this->file_path);
}

set<string> Input_Reader::get_terminals() {
    return this->terminals;
}

map<string, vector<Entry> > Input_Reader::get_grammar() {
    return this->grammar;
}

void Input_Reader::read_file(string file_path) {
    // Ektibha ya HINDAWAAAAAAAAAAAAAAAAAAAAAY !
}

