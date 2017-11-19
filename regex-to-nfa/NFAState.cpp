//
// Created by abdelrahman on 12/11/17.
//

#include "NFAState.h"

int NFAState::current_id = 0;

NFAState::NFAState() {
    id = current_id++;
    accept_token_name = "";
    priority = -1;
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
    return accept_token_name == "";
}

void NFAState::setAccepting(std::string accept_token_name) {
    this->accept_token_name = accept_token_name;
    priority = 0; // default value (highest priority)
}

std::string NFAState::get_accept_token_name() {
    return accept_token_name;
}

void NFAState::setPriority(int priority) {
    this->priority = priority;
}

int NFAState::getPriority(int priority) {
    return priority;
}
