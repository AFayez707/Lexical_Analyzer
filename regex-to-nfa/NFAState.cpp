//
// Created by abdelrahman on 12/11/17.
//

#include "NFAState.h"
#include "IDGenerator.h"

NFAState::NFAState() {
    id = IDGenerator::getNextID();
    isAccepting = false;
}

int NFAState::get_id() {
    return id;
}

NFAState* NFAState::get_transition_On(char c) {
    if(transitions.find(c) == transitions.end())
        return 0;
    return transitions[c];
}

void NFAState::set_transition_On(char c, NFAState *next) {
    transitions[c] = next;
}

void NFAState::add_epsilon_transition(NFAState *next) {
    epsilon_transitions.push_back(next);
}

std::vector<NFAState*> NFAState::get_epsilon_transitions() {
    return epsilon_transitions;
}

bool NFAState::is_accepting() {
    return isAccepting;
}

void NFAState::setAccepting(bool isAccepting) {
    this->isAccepting = isAccepting;
}