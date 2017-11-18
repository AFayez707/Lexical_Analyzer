//
// Created by ahmed on 14/11/17.
//

#ifndef LEXICAL_ANALYZER_DFA_H
#define LEXICAL_ANALYZER_DFA_H

#include <set>
#include "../regex-to-nfa/nfa.h"

struct transition {
    int from;
    int to;
    char value;
};

class dfa {

public:
    dfa::dfa(nfa *n,  set<char> language);
    std::set<int> get_states();
    bool is_accepting(int state_id);
    int transitions_to(int state, char c);

private:
    // set of DFA states

    vector<transitions>     transitions;
    vector<vector<int>>     entries;
    vector<bool>            isMarked;
    vector<int>             finalStates;

    vector<int> set_to_vector(set<int> set);
    set<int> vector_to_set(vector<int> vector);
    int FindEntry(vector<int> entry);
    int GetNextUnMarkedIndex();
    int AddEntry(vector<int> entry);
    void MarkEntry(int index);
    vector<int> GetEntry(int index);
    void SetFinalState(int nfa_fs);

    void SetTransition(int from, int to, char value);

    void display();

    string GetFinalState();
};


#endif //LEXICAL_ANALYZER_DFA_H
