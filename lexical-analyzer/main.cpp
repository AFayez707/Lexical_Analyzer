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
    string grammar_file, source_code_file, log_to_file;

    if (argc == 1) {
        fprintf(stdout, "using default files, writing all output to log.txt\n");
        source_code_file = "source.txt";
        grammar_file = "grammar.txt";
        freopen("log.txt", "w", stdout);
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
    minimized_dfa.display();
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

    string log_to_file;
    fprintf(stdout, "write to log file (Y/N): ");
    cin >> log_to_file;
    if (log_to_file == "Y" || log_to_file == "y") {
        fprintf(stdout, "all output is written to log.txt\n");
        freopen("log.txt", "w", stdout);
    }
}
