//
// Created by ahmed on 11/13/17.
//

#include "State.h"

unsigned int State::state_count = 1;

State::State() {
    this->state_id = state_count++;
}

bool State::is_accept_state() const {
    return this->accept_state;
}

void State::set_accept_state(bool is_accept_state) {
    this->accept_state = is_accept_state;
}

int State::get_state_id() const {
    return this->state_id;
}

void State::set_state_id(unsigned int id) {
    this->state_id = id;
}

void State::set_transition(State *next, string input) {
    this->transitions[input] = next;
}

State *State::get_transition_on(string input) {
    return this->transitions[input];
}

void State::set_epsilon_transition(State *state) {
    this->epsilon_transitions.push_back(state);
}

vector<State *> State::get_epsilon_transitions() const {
    return this->epsilon_transitions;
}

map<string, State *> State::get_transitions() const {
    return this->transitions;
}

void State::set_token_type(string token_type) {
    this->token_type = std::move(token_type);
}

string State::get_token_type() const {
    return this->token_type;
}

bool State::is_input_state() const {
    return input_state;
}

void State::set_input_state(bool input_state) {
    State::input_state = input_state;
}
