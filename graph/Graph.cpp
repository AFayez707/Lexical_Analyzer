//
// Created by ahmed on 11/13/17.
//

#include "Graph.h"

#include <utility>

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

int Graph::get_state_count() {
    std::set<State *> vis;
    return count_states(this->get_start_state(), vis);
}

// Just a simple DFS
int Graph::count_states(State *state, set<State *> vis) {
    if (vis.find(state) != vis.end()) return 0;
    vis.insert(state);
    int state_count = 1;
    vector<Edge> *out_edges = state->get_out_edges();
    for (auto &edge : *out_edges) {
        State *to = edge.get_to_state();
        state_count += count_states(to, vis);
    }
    return state_count;
}

set<State *> Graph::get_states() {
    return this->states;
}

void Graph::set_states(set<State *> states) {
    this->states = std::move(states);
}

void Graph::insert_state(State *state) {
    this->states.insert(state);
}
