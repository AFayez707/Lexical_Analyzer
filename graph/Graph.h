//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_GRAPH_H
#define LEXICAL_ANALYZER_GRAPH_H

#include <set>
#include "State.h"

class Graph {
public:
    Graph();

    explicit Graph(State *start);

    void set_start_state(State *state);

    State *get_start_state();

    void set_end_state(State *state);

    State *get_end_state();

    set<State *> get_states();

    void insert_state(State *state);

private:
    State *start_state;
    State *end_state;
    set<State *> states;
};

#endif //LEXICAL_ANALYZER_GRAPH_H
