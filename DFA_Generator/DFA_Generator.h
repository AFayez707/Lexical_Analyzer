//
// Created by ahmed on 14/11/17.
//

#ifndef LEXICAL_ANALYZER_DFA_H
#define LEXICAL_ANALYZER_DFA_H

#include <set>
#include "../regex-to-nfa/NFA.h"
#include "../graph/Graph.h"

struct transition {
    int from;
    int to;
    char value;
};

class DFA {

public:
    DFA(NFA *n, set<char> language);

    void display();

    Graph *as_graph();

//    bool is_accept_state(int id);
//    int transitions_to(int state, char c);
//    set<int> get_states();

private:

    // set of DFA states
    vector<transition> transitions;
    vector<vector<int>> entries;
    vector<bool> isMarked;

    vector<string> finalStateTokenNames;
    vector<int> finalStates;

    vector<int> set_to_vector(set<int> set);

    set<int> vector_to_set(vector<int> vector);

    int FindEntry(vector<int> entry);

    int GetNextUnMarkedIndex();

    int AddEntry(vector<int> entry);

    void MarkEntry(int index);

    vector<int> GetEntry(int index);

    void SetDFAFinalState(int dfa_fs, string token_name);

    void SetNFAFinalState(int nfa_fs);

    void SetTransition(int from, int to, char value);

    string GetFinalState();

    string join(vector<int> vector, string delimiter);

};


#endif //LEXICAL_ANALYZER_DFA_H
