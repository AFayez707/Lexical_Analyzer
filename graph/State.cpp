//
// Created by ahmed on 11/13/17.
//


#include "State.h"

unsigned int State::state_count = 1;

State::State() {
    this->id = state_count++;
}

bool State::is_accept_state() const {
    return this->token_name != "undefined";
}

void State::set_accept_state(string token_name) {
    this->token_name = std::move(token_name);
    this->priority = 0; // default value (highest priority)
}

int State::get_id() const {
    return this->id;
}

void State::set_id(unsigned int id) {
    this->id = id;
}

void State::add_transition(char input, State *next) {
    this->transitions[input] = next;
}

State *State::get_transition_on(char input) {
    if (transitions.find(input) == transitions.end())
        return nullptr;
    return this->transitions[input];
}

void State::add_epsilon_transition(State *state) {
    this->epsilon_transitions.push_back(state);
}

vector<State *> State::get_epsilon_transitions() const {
    return this->epsilon_transitions;
}

map<char, State *> State::get_transitions() const {
    return this->transitions;
}

void State::set_token_name(string token_name) {
    this->token_name = std::move(token_name);
}

string State::get_token_name() const {
    return this->token_name;
}

bool State::is_input_state() const {
    return input_state;
}

void State::set_input_state(bool input_state) {
    State::input_state = input_state;
}

void State::set_priority(int priority) {
    this->priority = priority;
}

int State::get_priority() {
    return this->priority;
}
