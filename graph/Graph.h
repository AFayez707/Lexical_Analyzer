//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_GRAPH_H
#define LEXICAL_ANALYZER_GRAPH_H

#include "State.h"

class Graph {
public:
    Graph();

    explicit Graph(State *start);

    void set_start_state(State *state);

    State *get_start_state();

    void set_end_state(State *state);

    State *get_end_state();

    int get_state_count();

private:
    State *start_state;
    State *end_state;

    int count_states(State *state, set<State *> vis);
};

#endif //LEXICAL_ANALYZER_GRAPH_H
