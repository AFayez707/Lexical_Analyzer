#include <iostream>
using namespace std;

class nfa {
private:
    int start_state, end_state;


public:
    void nfa::kleene_closure();

    void nfa::positive_closure();

    /**
     * concatenates this NFA with n by creating an NFA that accepts the concatenation set of
     * strings accepted by this and the set of strings accepted by n.
     */
    void nfa::concatenate(nfa n);

    void nfa::alternate(nfa n);

    void nfa::existance(nfa n); // set to name of question mark operator

    set<int> nfa::epsilon_closure(set<int> state_ids);

    set<int> nfa::move(set<int> state_ids, char c);

    bool nfa::is_accepting(int state_id);

    int nfa::get_start_state();

};
