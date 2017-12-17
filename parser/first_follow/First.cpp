//
// Created by ahmed on 12/11/17.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include "First.h"

First::First(string start_symbol, GRAMMAR grammar, set<string> terminals) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);
    this->terminals = move(terminals);

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
}

void First::__generate(){

    cout << "===First Generating===" << endl;

    for (auto& element : grammar){
        cout << "Now calculating first for: " << element.first << endl;
        set<string> resultSet = calculateFirst(element.first);

        first[element.first]=resultSet;
    }
    
    // Testing purposes
    for (auto& t : first){
        cout << "Firsts(" << t.first << ") = { ";

        for (auto elem : t.second){
            cout << elem << ", ";
        }
        cout << " }" << endl;
    }
}

set<string> First::calculateFirst(string key){

    set<string> firsts;

    for(int i=0; i< grammar[key].size(); i++){

        if(terminals.count(grammar[key][i][0])){ // If Terminal
            firsts.insert(grammar[key][i][0]);
        }
        else if (grammar[key][i][0] == key){
            continue;
        }
        else{ // Not terminal
            set<string> result = calculateFirst(grammar[key][i][0]);
            firsts.insert(result.begin(), result.end());
        }
    }
    return firsts;
}