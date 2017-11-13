#include <iostream>
#include <set>

using namespace std;

class nfa {
private:
    int start_state, end_state;


public:
    /**
     * creates an nfa that accepts only the character c
     */
    nfa(char c);

    void kleene_closure();

    void positive_closure();

    /**
     * concatenates this NFA with n by creating an NFA that accepts the concatenation set of
     * strings accepted by this and the set of strings accepted by n.
     */
    void concatenate(nfa* n);

    void alternate(nfa* n);

    // void existance(nfa n); // set to name of question mark operator

    set<int> epsilon_closure(set<int> state_ids);

    set<int> move(set<int> state_ids, char c);

    bool is_accepting(int state_id);

    int get_start_state();

};
