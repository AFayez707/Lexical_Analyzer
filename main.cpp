// TODO : To be implemented
#include <iostream>
#include "regex-to-nfa/construct_nfa.h"
#include "DFA_Generator/dfa.h"

using namespace std;

int main() {
    string regex1 = "ab|c."; // (a|b)c
    nfa *n1 = regex_to_nfa(regex1);

    string regex2 = "a*b+|"; // a*|b+
    nfa *n2 = regex_to_nfa(regex2);

    vector<nfa*> list;
    list.push_back(n2);
    n1->combine(list);

    set<char> language;
    language.insert('a');
    language.insert('b');
    language.insert('c');

    dfa dfa(n1, language);
    cout << "Hello World!" << endl;

    dfa.display();

    return 0;
}
