#include "nfa.h"

nfa::nfa(char c) {
    start = new NFAState();
    end = new NFAState();
    start->set_transition_On(c, end);
}

void nfa::kleene_closure() {}

void nfa::positive_closure() {}

void nfa::concatenate(nfa* n) {}

void nfa::alternate(nfa* n) {}

set<int> epsilon_closure(set<int> state_ids) {}

set<int> move(set<int> state_ids, char c) {}

bool is_accepting(int state_id) {}