// TODO : To be implemented
#include <iostream>
#include "regex-to-nfa/construct_nfa.h"


using namespace std;

int main() {
    string regex = "ab|c.";

    nfa *n = regex_to_nfa(regex);

    n->print_dfs();

    set<int> start;
    start.insert(n->get_start_state());
    set<int> eps = n->epsilon_closure(start);
    if(eps.find(2) != eps.end())
        cout << "(2 exits)" << endl;


    cout << "Hello World!" << endl;
    return 0;
}
