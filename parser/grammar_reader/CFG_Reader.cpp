//
// Created by ahmed on 12/5/17.
//

#include "CFG_Reader.h"
#include <iomanip>

CFG_Reader::CFG_Reader(string file_path) {
    this->file_path = move(file_path);

    __read(this->file_path);
}

GRAMMAR CFG_Reader::get_grammar() {
    return this->grammar;
}

set<string> CFG_Reader::get_terminals() {
    return this->terminals;
}

string CFG_Reader::get_start_symbol() {
    return this->start_symbol;
}

void CFG_Reader::log(ofstream *log_file) {
    *log_file << left << "\n\nTerminals:\n    ";
    for (const string &t: this->terminals)
        *log_file << t << "    ";

    *log_file << "\n\nStart Symbol: " << start_symbol << "\n\nGrammar: \n";

    for (auto &rule: this->grammar) {
        *log_file << "    # " << setw(18) << rule.first << "➜ ";
        for (int i = 0; i < rule.second.size(); i++) {
            for (const string &j : rule.second[i])
                *log_file << j << " ";

            *log_file << (i < rule.second.size() - 1 ? "| " : "");
        }
        *log_file << endl;
    }
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
    // \L           -> EPSILON

    while (true) {
        int c = file.get();

        str = str == "\\L" ? EPS : str;

        if (c == EOF) {
            str.length() ? production.emplace_back(str) : void();
            !production.empty() ? grammar[LHS].emplace_back(production) : void();
            break;
        } else if (c == '#') {
            !production.empty() ? grammar[LHS].emplace_back(production) : void();
            LHS_lock = true;
            str = "";
        } else if (c == '\'') {
            comma_lock ? void(this->terminals.insert(str)) : void();
            comma_lock = !comma_lock;
        } else if (c == '=' && !comma_lock) {
            production.clear();
        } else if (c == '|') {
            grammar[LHS].emplace_back(production);
            production.clear();
        } else if (c == ' ' || c == '\t' || c == '\n') {
            if (!str.empty()) {
                LHS_lock ? void(LHS = str) : production.emplace_back(str);
                start_symbol = start_symbol.empty() ? LHS : start_symbol;
                LHS_lock = false;
                str = "";
            }
        } else
            str.push_back((char) c);
    }
    file.close();
}
