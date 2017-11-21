//
// Created by abdelrahman on 20/11/17.
//

#include <iostream>
#include <set>

#include "regex-to-nfa/NFA.h"
#include "regex-to-nfa/construct_NFA.h"
#include "dfa_reduction/DFA_Reducer.h"
#include "dfa_generator/DFA_Generator.h"
#include "regex-to-nfa/Regex.h"


int main() {
    string grammar_file_path;

    grammar_file_path = "grammar.txt";

    Regex regex_library(grammar_file_path);

    regex_library.parse2();
    vector<pair<string, string>> simple_language_regexes = regex_library.expressions;

    set<char> language = regex_library.language_characters;

    NFA *language_nfa = language_to_nfa(simple_language_regexes);

    DFA language_dfa(language_nfa, language);
    language_dfa.display();


    Graph *g = language_dfa.as_graph();
    DFA_Reducer reducer(g, language);
    reducer.minimize();
    reducer.print();

    string source_code;
    freopen("source.txt", "r", stdin);
    source_code.clear();

    while (true) {
        int c = getchar();

        if (c == EOF) {
            reducer.simulate(source_code);
            break;
        }
        if (c == ' ' | c == '\t' | c == '\n' && !source_code.empty()) {
            reducer.simulate(source_code);
            source_code = "";
            continue;
        }
        if (c == ' ' | c == '\t' | c == '\n' | c == EOF)
            continue;

        source_code.push_back((char) c);
    }
    printf("\nParsing done succesfully !\n");
    return 0;
}