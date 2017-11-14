//
// Created by abdelrahman on 14/11/17.
//

#ifndef LEXICAL_ANALYZER_DFA_H
#define LEXICAL_ANALYZER_DFA_H

#include <set>

class dfa {

public:
    std::set<int> get_states();
    bool is_accepting(int state_id);
    int transitions_to(int state, char c);

private:
    // set of DFA states

    // Transition table

};


#endif //LEXICAL_ANALYZER_DFA_H
