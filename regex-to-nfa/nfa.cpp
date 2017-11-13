#include "nfa.h"

nfa::nfa() {

}


nfa::kleene_closure() {}

nfa::positive_closure() {}

nfa::concatenate(nfa n) {}

nfa::alternate(nfa n) {}

set<int> epsilon_closure(set<int> state_ids) {}

set<int> move(set<int> state_ids, char c) {}

bool is_accepting(int state_id) {}