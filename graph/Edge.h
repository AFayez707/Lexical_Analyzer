//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_EDGE_H
#define LEXICAL_ANALYZER_EDGE_H

#include <iostream>

// Need this to avoid recursive include
class State;

using namespace std;

class Edge {
public:
    Edge() = default;

    Edge(State *from, State *to, string weight);

    string get_weight();

    State *get_from_state();

    State *get_to_state();

private:
    string weight;
    State *from{};
    State *to{};
};

#endif //LEXICAL_ANALYZER_EDGE_H
