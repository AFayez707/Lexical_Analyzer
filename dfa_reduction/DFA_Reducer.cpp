//
// Created by ahmed on 11/14/17.
//

#include <map>
#include "DFA_Reducer.h"

DFA_Reducer::DFA_Reducer(Graph *dfa) {
    this->dfa = dfa;
}

Graph *DFA_Reducer::get_dfa() {
    return this->dfa;
}

Graph *DFA_Reducer::remove_redundancies() {
    cout << "\n\nEliminating redundancies:\n=========================\n";
    set<State *> states = dfa->get_states();
    map<pair<int, State *>, pair<int, State *> > redundancies;
    vector<State *> states_vector;

    for (auto &state: states) {
        states_vector.push_back(state);
    }

    // Check for redundancies
    for (int i = 0; i < states_vector.size(); ++i) {
        State *A = states_vector[i];
        for (int j = i + 1; j < states_vector.size(); ++j) {
            State *B = states_vector[j];
            bool valid = false;
            if (A->get_out_edges()->size() == B->get_out_edges()->size() &&
                A->is_accept_state() == B->is_accept_state()) {
                for (auto &k : *A->get_out_edges()) {
                    valid = false;
                    State *nextA = k.get_to_state();
                    string inputA = k.get_weight();

                    for (auto &l : *B->get_out_edges()) {
                        State *nextB = l.get_to_state();
                        string inputB = l.get_weight();
                        if (inputA == inputB && nextA == nextB) {
                            valid = true;
                            break;
                        }
                    }
                    if (valid)
                        continue;
                    else
                        break;
                }
                if (valid) {
                    redundancies[{A->get_state_id(), A}] = {B->get_state_id(), B};
                }
            }
        }
    }

    // Replace redundancies in the graph
    for (auto &redundant: redundancies) {
        cout << "Redundant: " << redundant.first.first << " ==> " << redundant.second.first << "\n";
        states.erase(redundant.second.second);
        for (auto &state : states) {
            for (auto &edge : *state->get_out_edges()) {
                // Update pointer
                if (edge.get_to_state() == redundant.second.second) {
                    edge.set_to_state(redundant.first.second);
                }
            }
            for (auto &next: state->transitions) {
                if (next.second == redundant.second.second)
                    next.second = redundant.first.second;
            }
        }
    }

    this->dfa->set_states(states);
    for (auto &state: states) {
        cout << "State: " << state->get_state_id() << " =>";
        for (auto &edge: *state->get_out_edges()) {
            cout << "  -  " << edge.get_to_state()->get_state_id();
        }
        cout << "\n";
    }
}

Graph *DFA_Reducer::minimize() {
    int parent = 3;
    map<int, set<State *>> disjoint_set;
    map<State *, int> state_set;

    for (auto &state: this->get_dfa()->get_states()) {
        if (state->is_accept_state()) {
            disjoint_set[1].insert(state);
            state_set[state] = 1;
        } else {
            disjoint_set[2].insert(state);
            state_set[state] = 2;
        }
    }

    bool flag = true;
    while (flag) {
        flag = false;
        for (auto &cur_set: disjoint_set) {
            for (auto &state1: cur_set.second) {
                for (auto &state2: cur_set.second) {
                    if (state1 == state2) continue;
                    for (auto &transition: state1->transitions) {
                        if (state_set[transition.second] != state_set[state2->transitions[transition.first]]) {
                            if (state_set[state1] != state_set[transition.second]) {
                                state_set[state1] = parent;
                                cur_set.second.erase(state1);
                                disjoint_set[parent++].insert(state1);
                            } else {
                                state_set[state2] = parent;
                                cur_set.second.erase(state2);
                                disjoint_set[parent++].insert(state2);
                            }
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
        }
    }

    map<pair<int, string>, int> transition;
    set<string> lang;
    set<int> min_state;

    // form transition table
    for (auto &state: state_set) {
        min_state.insert(state.second);
        for (auto &move: state.first->transitions) {
            lang.insert(move.first);
            transition[make_pair(state_set[state.first], move.first)] = state_set[move.second];
        }
    }
    cout << left;
    cout << "\n\nMinimized DFA:\n";
    cout << "==============\n     |input";
    for (auto &input:lang) {
        cout << "   |\"" << input << "\"";
    }

    cout << "\n";

    cout << "-------------------------\n";
    for (auto &state: min_state) {
        printf("%-5d|        ", state);
        for (auto &input:lang) {
            printf("|%-6d", transition[make_pair(state, input)]);
        }
        cout << "\n";
    }

//    for (auto &move: transition) {
//        cout << move.first.first << " + \"" << move.first.second << "\" ==> " << move.second << "\n";
//    }
}
