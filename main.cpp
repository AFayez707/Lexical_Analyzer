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


    freopen("source.txt", "r", stdin);
    string source_code;

    while (1) {
        int c = getchar();

        if(c == EOF)
            break;

        source_code.push_back((char) c);
    }

    language_dfa.simulate(source_code);


//    Graph *g = language_dfa.as_graph();
//    DFA_Reducer reducer(g, language);
//    reducer.print();
//    reducer.minimize();
//    reducer.print();

    return 0;
}