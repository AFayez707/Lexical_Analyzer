//
// Created by abdelrahman on 12/11/17.
//

#ifndef LEXICAL_ANALYZER_NFASTATE_H
#define LEXICAL_ANALYZER_NFASTATE_H

#include <unordered_map>
#include <vector>

class NFAState {
public:
    NFAState();
    bool is_accepting();
    void setAccepting(bool isAccepting);
    int get_id();
    NFAState* get_transition_On(char c);
    void set_transition_On(char c, NFAState* next);
    std::vector<NFAState*> get_epsilon_transitions();
    void add_epsilon_transition(NFAState* next);

private:
    int id;
    bool isAccepting;
    static int current_id;
    std::unordered_map<char, NFAState*> transitions;
    std::vector<NFAState*> epsilon_transitions;
};


#endif //LEXICAL_ANALYZER_NFASTATE_H
