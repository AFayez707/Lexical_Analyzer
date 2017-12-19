//
// Created by ahmed on 12/11/17.
//

#include <iomanip>
#include "Left_Recursion.h"

Left_Recursion::Left_Recursion(GRAMMAR grammar, map<string, int> order, set<string> terminals, vector<string> ordered_grammar) {
    this->grammar = move(grammar);
    this->order = move(order);
    this->terminals = move(terminals);
    this->ordered_grammar = move(ordered_grammar);

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
    int a;
    // just passing the grammar as it came here
    this->ambiguity_free_grammar = this->grammar;

    for (auto &y : ordered_grammar) {
        pair<string, vector<vector<string > > > rule = make_pair(y, this->ambiguity_free_grammar[y]);
        for (int i = 0; i < rule.second.size(); i++) {
            for (int j =0; j < rule.second.size(); j++) { /// --> Non-Immediate Recursion Removal Here
                if(this->terminals.find(rule.second[j][0]) == this->terminals.end() &&
                        this->order[rule.second[j][0]] < this->order[rule.first]){
                    string higher_term = rule.second[j][0];
                    rule.second[j].erase(rule.second[j].begin());
                    vector<string> gamma = rule.second[j];
                    rule.second.erase(rule.second.begin() + j);
                    for(int x = 0; x < this->ambiguity_free_grammar[higher_term].size(); x++){
                        vector<vector<string > > temp_rule = this->ambiguity_free_grammar[higher_term];
                        temp_rule[x].insert(temp_rule[x].end(), gamma.begin(), gamma.end());
                        rule.second.push_back(temp_rule[x]);
                    }
                }
            }
            if (rule.first == rule.second[i][0]) { /// --> Immediate Recursion Removal Here
                for (a = 0; a < rule.second.size(); a++) {
                    if (rule.first != rule.second[a][0] && rule.second[a].back() != (rule.first + "'"))
                        rule.second[a].push_back(rule.first + "'");
                    else {
                        rule.second[a].erase(rule.second[a].begin());
                        vector<string> alpha = rule.second[a];
                        rule.second.erase(rule.second.begin() + a);
                        alpha.push_back(rule.first + "'");
                        new_rule.push_back(alpha);
                        a--;
                    }
                }
                if (a >= rule.second.size() - 1) {
                    new_rule.push_back({EPS}); // NOLINT
                    this->ambiguity_free_grammar[rule.first] = rule.second;
                    this->ambiguity_free_grammar.insert({rule.first + "'", new_rule});
                    new_rule.clear();
                }
            }
        }
    }
}
