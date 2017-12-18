//
// Created by ahmed on 12/11/17.
//

#include <iomanip>
#include "Left_Recursion.h"

Left_Recursion::Left_Recursion(string start_symbol, GRAMMAR grammar, map<string, int> order) {
    this->start_symbol = move(start_symbol);
    this->grammar = move(grammar);
    this->order = move(order);

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
    vector<vector<string> > new_rule;
    vector<string> epsilon ({EPS});
    int a;
    // just passing the grammar as it came here
    this->ambiguity_free_grammar = this->grammar;

    for (auto &rule: this->ambiguity_free_grammar) {
        for (int i = 0; i < rule.second.size(); i++) {
            for (const string &j : rule.second[i]) {
//                *log_file << j << " ";
            }
            if(rule.first == rule.second[i][0]){                               //// --> Immediate Recursion Removal Here
                for (a = 0; a < rule.second.size(); a++) {
                    if(rule.first != rule.second[a][0] && rule.second[a].back() != (rule.first+"'"))
                        rule.second[a].push_back(rule.first+"'");
                    else{
                        rule.second[i].erase(rule.second[i].begin());
                        vector<string> alpha = rule.second[i];
                        rule.second.erase(rule.second.begin()+i);
                        alpha.push_back(rule.first + "'");
                        new_rule.push_back(alpha);
                        a--;
                    }
                }
                if(a >= rule.second.size() - 1){
                    new_rule.push_back(epsilon);
                    this->ambiguity_free_grammar[rule.first] = rule.second;
                    this->ambiguity_free_grammar.insert({rule.first+"'", new_rule});
                    new_rule.clear();
                }
            }
        }
    }
}
