//
// Created by ahmed on 21/11/17.
//

#include "regex-to-nfa/NFA.h"
#include "regex-to-nfa/construct_NFA.h"
#include "dfa_reduction/DFA_Reducer.h"
#include "dfa_generator/DFA_Generator.h"
#include "regex-to-nfa/Regex.h"

void check_files(string &grammar_file, string &source_code_file) {
    ifstream f1(grammar_file.c_str());
    if (!f1.good()) {
        fprintf(stderr, "could find/open grammar file.\n");
        exit(1);
    }

    ifstream f2(source_code_file.c_str());
    if (!f2.good()) {
        fprintf(stderr, "could find/open source code file.\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    auto *log_file = new ofstream("lex-log.txt", ios_base::out);
    *log_file << left;

    string grammar_file, source_code_file;

    if (argc == 1) {
        grammar_file = "grammar.txt";
        source_code_file = "source.txt";
    } else if (argc == 3) {
        grammar_file = string(argv[1]);
        source_code_file = string(argv[2]);
    } else {
        fprintf(stderr, "Invalid number of params, it takes zero or two params only !\n\n"
                "to use default files: ./lexical_analyzer\n\n"
                "    to use any files: ./lexical_analyzer [grammar file path] [source code file path]\n\n"
                "Note: default file are files found in the same dir with names `grammar.txt` & `source.txt`\n\n");
        exit(1);
    }

    check_files(grammar_file, source_code_file);

    // Parse grammar file, and form language chars
    Regex regex_library(grammar_file, log_file);
    regex_library.parse();
    vector<pair<string, string>> simple_language_regex = regex_library.expressions;
    set<char> language_chars = regex_library.language_characters;

    // Built NFA
    NFA *nfa = language_to_nfa(simple_language_regex);

    // Convert NFA to DFA
    DFA dfa(nfa, language_chars, log_file);

    // Minimize DFA
    DFA_Reducer minimized_dfa(dfa.as_graph(), language_chars);
    minimized_dfa.minimize();
    minimized_dfa.log(log_file);
    minimized_dfa.tokenize(source_code_file);

    log_file->close();
    return 0;
}
