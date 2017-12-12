//
// Created by ahmed on 21/11/17.
//

#include <zconf.h>
#include <fstream>
#include "regex-to-nfa/NFA.h"
#include "regex-to-nfa/construct_NFA.h"
#include "dfa_reduction/DFA_Reducer.h"
#include "dfa_generator/DFA_Generator.h"
#include "regex-to-nfa/Regex.h"

void init(string &grammar_file, string &source_code_file);

int main(int argc, char *argv[]) {
    auto *log_file = new ofstream("lex-log.txt", ios_base::out);
    *log_file << left;

    string grammar_file, source_code_file;

    if (argc == 1) {
        source_code_file = "source.txt";
        grammar_file = "grammar.txt";
    } else {
        init(grammar_file, source_code_file);
    }

    // Parse grammar file, and form language chars
    Regex regex_library(grammar_file);
    regex_library.parse();
    vector<pair<string, string>> simple_language_regex = regex_library.expressions;
    set<char> language_chars = regex_library.language_characters;

    // Built NFA
    NFA *nfa = language_to_nfa(simple_language_regex);

    // Convert NFA to DFA
    DFA dfa(nfa, language_chars);
//    dfa.display();

    // Minimize DFA
    DFA_Reducer minimized_dfa(dfa.as_graph(), language_chars);
    minimized_dfa.minimize();
    minimized_dfa.log(log_file);
    minimized_dfa.tokenize(source_code_file);

    return 0;
}

void init(string &grammar_file, string &source_code_file) {
    fprintf(stdout, "Grammar file: ");
    cin >> grammar_file;
    if (access(grammar_file.c_str(), F_OK) == -1) {
        fprintf(stderr, "could find/open grammar file.\n");
        exit(1);
    }

    fprintf(stdout, "Source code file: ");
    cin >> source_code_file;
    if (access(source_code_file.c_str(), F_OK) == -1) {
        fprintf(stderr, "could find/open grammar file.\n");
        exit(1);
    }
}
