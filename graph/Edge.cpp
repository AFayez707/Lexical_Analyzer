//
// Created by ahmed on 11/13/17.
//

#include "Edge.h"

Edge::Edge(State *from, State *to, string weight) {
    this->from = from;
    this->to = to;
    this->weight = std::move(weight);
}

State *Edge::get_from_state() {
    return this->from;
}

State *Edge::get_to_state() {
    return this->to;
}

string Edge::get_weight() {
    return this->weight;
}
