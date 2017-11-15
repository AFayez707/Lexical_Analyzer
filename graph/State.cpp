//
// Created by ahmed on 11/13/17.
//

#include "State.h"

int State::state_count = 1;

State::State() {
    this->state_id = state_count++;
}

vector<Edge> *State::get_out_edges() {
    return &children;
}

void State::add_child(State *child, string weight) {
    Edge edge(this, child, std::move(weight));
    children.push_back(edge);
}

void State::set_accept_state(bool is_accept_state) {
    this->accept_state = is_accept_state;
}

bool State::is_accept_state() {
    return this->accept_state;
}

void State::set_token_type(string token_type) {
    this->token_type = std::move(token_type);
}

string State::get_token_type() {
    return token_type;
}

int State::get_state_id() {
    return this->state_id;
}
