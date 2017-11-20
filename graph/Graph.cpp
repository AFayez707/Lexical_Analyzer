//
// Created by ahmed on 11/13/17.
//

#include "Graph.h"

Graph::Graph() {
    this->start_state = new State();
    this->end_state = new State();
}

Graph::Graph(State *start) {
    this->start_state = start;
    this->end_state = new State();
}

void Graph::set_start_state(State *state) {
    this->start_state = state;
}

State *Graph::get_start_state() {
    return this->start_state;
}

void Graph::set_end_state(State *state) {
    this->end_state = state;
}

State *Graph::get_end_state() {
    return this->end_state;
}

unsigned long Graph::get_state_count() {
    return this->states.size();
}

set<State *> Graph::get_states() {
    return this->states;
}

void Graph::erase_state(State *state) {
    this->states.erase(state);
}

void Graph::insert_state(State *state) {
    this->states.insert(state);
}
