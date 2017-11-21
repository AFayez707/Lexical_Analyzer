//
// Created by ahmed on 21/11/17.
//

#include <zconf.h>
#include "regex-to-nfa/NFA.h"
#include "regex-to-nfa/construct_NFA.h"
#include "dfa_reduction/DFA_Reducer.h"
#include "dfa_generator/DFA_Generator.h"
#include "regex-to-nfa/Regex.h"

void match_source_code(DFA_Reducer minimized_dfa, const string &source_code_file) {
    printf("\n\nParsing source code..\n\n");
    string source_code;
    freopen(source_code_file.c_str(), "r", stdin);

    while (true) {
        int c = getchar();

        if (c == EOF) {
            minimized_dfa.simulate(source_code);
            break;
        }
        if (c == ' ' | c == '\t' | c == '\n' && !source_code.empty()) {
            minimized_dfa.simulate(source_code);
            source_code = "";
            continue;
        }
        if (c == ' ' | c == '\t' | c == '\n' | c == EOF)
            continue;

        source_code.push_back((char) c);
    }
    printf("\nParsing done successfully !\n");
}

int main() {
    string log_file = "log.txt";
    string grammar_file = "grammar.txt";
    string source_code_file = "source.txt";

    // Redirect output from stdout to log file
    freopen(log_file.c_str(), "w", stdout);

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
    DFA_Reducer reducer(dfa.as_graph(), language_chars);
    reducer.minimize();
    reducer.display();

    match_source_code(reducer, source_code_file);
    return 0;
}
