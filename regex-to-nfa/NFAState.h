//
// Created by abdelrahman on 12/11/17.
//

#ifndef LEXICAL_ANALYZER_NFASTATE_H
#define LEXICAL_ANALYZER_NFASTATE_H

#include <unordered_map>
#include <vector>
#include <string>

class NFAState {
public:
    NFAState();
    bool is_accepting();
    void setAccepting(std::string isAccepting);
    int get_id();
    NFAState* get_transition_On(char c);
    void set_transition_On(char c, NFAState* next);
    std::vector<NFAState*> get_epsilon_transitions();
    void add_epsilon_transition(NFAState* next);
    std::string get_accept_token_name();
    void setPriority(int priority);
    int getPriority(int priority);

private:
    int id;
    std::string accept_token_name;
    static int current_id;
    std::unordered_map<char, NFAState*> transitions;
    std::vector<NFAState*> epsilon_transitions;
    int priority;
};


#endif //LEXICAL_ANALYZER_NFASTATE_H
