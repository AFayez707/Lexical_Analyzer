//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_STATE_H
#define LEXICAL_ANALYZER_STATE_H

#include <iostream>
#include <vector>
#include "Edge.h"

using namespace std;

class State {
public:
    State();

    vector<Edge> *get_out_edges();

    void add_child(State *child, string weight);

    void set_accept_state(bool is_accept_state);

    bool is_accept_state();

    void set_token_type(string token_type);

    string get_token_type();

    int get_state_name();

    static int state_count;

private:
    int state_name = 0;
    string token_type = "";
    bool accept_state = false;
    vector<Edge> children;
};

#endif //LEXICAL_ANALYZER_STATE_H
