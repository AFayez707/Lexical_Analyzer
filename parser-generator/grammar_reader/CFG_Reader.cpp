//
// Created by ahmed on 12/5/17.
//

#include "CFG_Reader.h"
#include <fstream>

CFG_Reader::CFG_Reader(string file_path) {
    this->file_path = move(file_path);

    __read(this->file_path);
}

MSV CFG_Reader::get_grammar() {
    return this->grammar;
}

set<string> CFG_Reader::get_terminals() {
    return this->terminals;
}

void CFG_Reader::__read(string file_path) {
    ifstream file(file_path, ios_base::in);
    string str, LHS;
    bool LHS_lock = false, comma_lock = false;
    vector<string> production;

    //       #      -> new rule
    //       |      -> split with or
    //       =      -> rule definition
    //       '      -> terminal
    // \n \t space  -> token

    printf("\n\nReading context free grammar...\n");
    while (true) {
        int c = file.get();

        if (c == EOF) {
            str.length() ? production.emplace_back(str) : void();
            !production.empty() ? grammar[LHS].emplace_back(production) : void();
            break;
        } else if (c == '#') {
            !production.empty() ? grammar[LHS].emplace_back(production) : void();
            LHS_lock = true;
            str = "";
            continue;
        } else if (c == '\'') {
            comma_lock ? void(this->terminals.insert(str)) : void();
            comma_lock = !comma_lock;
            continue;
        } else if (c == '=' && !comma_lock) {
            production.clear();
            continue;
        } else if (c == '|') {
            grammar[LHS].emplace_back(production);
            production.clear();
            continue;
        } else if (c == ' ' || c == '\t' || c == '\n') {
            if (!str.empty()) {
                LHS_lock ? void(LHS = str) : production.emplace_back(str);
                LHS_lock = false;
                str = "";
            }
            continue;
        }
        str.push_back((char) c);
    }
    file.close();
    printf("Grammar read successfully !\n");
}

void CFG_Reader::display() {
    printf("\n\nTerminals:\n    ");
    for (const string &t: this->terminals)
        printf("%s    ", t.c_str());

    printf("\n\nGrammar: \n");
    for (auto &rule: this->grammar) {
        printf("    # %-18s➜ ", rule.first.c_str());
        for (int i = 0; i < rule.second.size(); i++) {
            for (const string &j : rule.second[i])
                printf("%s ", j.c_str());

            if (i < rule.second.size() - 1)
                printf("| ");
        }
        printf("\n");
    }
}
