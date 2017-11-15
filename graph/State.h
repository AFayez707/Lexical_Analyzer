//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_STATE_H
#define LEXICAL_ANALYZER_STATE_H

#include <vector>
#include <map>
#include <unordered_map>
#include "Edge.h"

class State {
public:
    State();

    bool is_accept_state();

    void set_accept_state(bool is_accept_state);

    int get_state_id();

    vector<Edge> *get_out_edges();

    void add_child(State *child, string weight);

    void set_token_type(string token_type);

    string get_token_type();

    static int state_count;

    unordered_map<string, State *> transitions;

private:
    int state_id = 0;
    string token_type = "";
    bool accept_state = false;
    vector<State *> epsilon_transitions;
    vector<Edge> children;
};

#endif //LEXICAL_ANALYZER_STATE_H
