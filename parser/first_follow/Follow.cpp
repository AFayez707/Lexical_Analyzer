//
// Created by ahmed on 12/11/17.
//

#define DOLLAR_SIGN "\\$\\"
#define EPS         "\\EPSILON\\"

#include <iomanip>
#include <iostream>
#include "Follow.h"

Follow::Follow(string start_symbol, GRAMMAR grammar, set<string> terminals, FIRST_FOLLOW first) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);
    this->terminals = move(terminals);
    this->first = move(first);

    __generate();
}

FIRST_FOLLOW Follow::get() {
    return this->follow;
}

void Follow::log(ofstream *log_file) {
    *log_file << "\n\nFollow:\n";
    for (pair<string, set<string>> entry: this->follow) {
        *log_file << "    " << setw(20) << entry.first << "  ➜  ";
        for (const string &str: entry.second) {
            if (entry.second.find(str) != entry.second.begin()) *log_file << "  ,  ";
            *log_file << str;
        }
        *log_file << endl;
    }
}

void Follow::__generate() {
    // Adding '$' to the start symbol
    follow[start_symbol].insert(DOLLAR_SIGN);

    for (auto &element : grammar) {
//        cout << "Now calculating Follow for: " << element.first << endl;
        set<string> resultSet = calculateFollow(element.first);
        follow[element.first].insert(resultSet.begin(), resultSet.end());
    }
}

set<string> Follow::calculateFollow(string key) {
    set<string> follows;
    for (auto LHS : grammar) {
        for (int j = 0; j < LHS.second.size(); j++) {
            for (int k = 0; k < LHS.second[j].size(); k++) {
                if (key == LHS.second[j][k]) {
                    if (k < LHS.second[j].size() - 1) { // If not the last
                        if (terminals.count(LHS.second[j][k + 1])) { // if the next is terminal
                            follows.insert(LHS.second[j][k + 1]);
                        } else if (LHS.second[j][k + 1] == LHS.second[j][k]) { // if the next = itself
                            continue;
                        } else { // if the next is non-terminal and not itself
                            follows.insert(first[LHS.second[j][k + 1]].begin(), first[LHS.second[j][k + 1]].end());

                            if (follows.count(EPS)) { // If the first contains EPS, Remove it then calculate it then add the follow of LHS
                                follows.erase(EPS);
                                set<string> result = calculateFollow(LHS.first);
                                follows.insert(result.begin(), result.end());
                            }
                        }
                    } else { // if it's the last

                        if(follow[LHS.first].size()){
                            follows.insert(follow[LHS.first].begin(), follow[LHS.first].end());
                            continue;
                        }

                        if(LHS.first == key){
                            continue;
                        }

                        set<string> result = calculateFollow(LHS.first);
                        follows.insert(result.begin(), result.end());

                        if (LHS.first == start_symbol) { // If the start symbol doesn't exist in any production rules as RHS
                            follows.insert(DOLLAR_SIGN);
                        }
                    }
                }
            }
        }
    }
    return follows;
}