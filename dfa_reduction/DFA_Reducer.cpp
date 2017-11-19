//
// Created by ahmed on 11/14/17.
//

#include "DFA_Reducer.h"

DFA_Reducer::DFA_Reducer(Graph *dfa, set<char> language_chars) {
    this->dfa = dfa;
    this->language_chars = std::move(language_chars);
}

Graph *DFA_Reducer::get_dfa() const {
    return this->dfa;
}

void DFA_Reducer::minimize() {
    // removes redundancies
    this->remove_redundancies();

//    this->print();

    // merging states using disjoint sets
    int partition_count = this->merge_nondistinguishable();
    this->min_dfa_builder(partition_count);
}

void DFA_Reducer::print() {
    set<State *> states = this->dfa->get_states();

    string line = "---------------";
    for (int i = 0; i < language_chars.size(); ++i)
        line += "--------";

    printf("%s\n               ", line.c_str());
    for (auto &input: this->language_chars) {
        printf("| %-5c", input);
    }

    printf("\n%s\n", line.c_str());
    for (auto &state: states) {
        if (state->is_input_state())
            printf(" ➜ ");
        else
            printf("   ");

        if (state->is_accept_state())
            printf("*");
        else
            printf(" ");

        printf("%5d  =>  ", state->get_state_id());
        for (auto &next_state: state->get_transitions()) {
            printf("| %-5d", next_state.second->get_state_id());
        }
        printf("\n");
    }
    printf("%s\n", line.c_str());
}

void DFA_Reducer::remove_redundancies() {
    printf("\nEliminating redundancies\n=========================\n");
    set<State *> states = dfa->get_states();
    map<State *, State *> redundant;

    for (auto &A: states) {
        states.erase(A);
        for (auto &B: states) {
            bool valid = false;
            // for dfa, must be always true.
            bool condition = A->get_transitions().size() == B->get_transitions().size();
            condition = condition && (A->is_accept_state() == B->is_accept_state());
            if (condition) {
                for (auto &nextA: A->get_transitions()) {
                    valid = false;
                    for (auto &nextB: B->get_transitions()) {
                        if (nextA.first == nextB.first && nextA.second == nextB.second) {
                            valid = true;
                            break;
                        }
                    }
                    if (!valid)
                        break;
                }
                if (valid) {
                    redundant[A] = B;
                }
            }
        }
    }

    // Replace redundancies in the graph
    for (auto &eq: redundant) {
        printf("Redundant: %-3d ==> %3d\n", eq.first->get_state_id(), eq.second->get_state_id());
        dfa->erase_state(eq.second);
        for (auto &state: dfa->get_states()) {
            for (auto &next_state: state->get_transitions()) {
                if (next_state.second == eq.second) {
                    state->set_transition(eq.first, next_state.first);
                }
            }
        }
        delete (eq.second);
    }
}

int DFA_Reducer::merge_nondistinguishable() {
    printf("\nMerging non-distinguishable states\n==================================\n");
    int partition_count = 2;
    map<int, set<State *> > disjoint_set;

    for (auto &state: this->get_dfa()->get_states()) {
        if (state->is_accept_state()) {
            disjoint_set[1].insert(state);
            this->old_state_mapper[state] = 1;
        } else {
            disjoint_set[2].insert(state);
            this->old_state_mapper[state] = 2;
        }
    }

    bool flag = true;
    while (flag) {
        flag = false;
        for (auto &cur_set: disjoint_set) {
            for (auto &stateA: cur_set.second) {
                for (auto &stateB: cur_set.second) {
                    if (stateA == stateB) continue;
                    for (auto &transition: stateA->get_transitions()) {
                        if (this->old_state_mapper[transition.second] !=
                            this->old_state_mapper[stateB->get_transitions()[transition.first]]) {
                            if (this->old_state_mapper[stateA] != this->old_state_mapper[transition.second]) {
                                this->old_state_mapper[stateA] = ++partition_count;
                                cur_set.second.erase(stateA);
                                disjoint_set[partition_count].insert(stateA);
                            } else {
                                this->old_state_mapper[stateB] = ++partition_count;
                                cur_set.second.erase(stateB);
                                disjoint_set[partition_count].insert(stateB);
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
    return partition_count;
}

void DFA_Reducer::min_dfa_builder(int partition_count) {
    set<int> min_state;
    // form transition_table table
    for (auto &state: this->old_state_mapper) {
        min_state.insert(state.second);
        for (auto &move: state.first->get_transitions()) {
            pair<int, char> cur_pair = make_pair(this->old_state_mapper[state.first], move.first);
            this->transition_table[cur_pair] = this->old_state_mapper[move.second];
        }
    }

    /*
     * building new min_dfa
     */
    delete (this->dfa);
    this->dfa = new Graph();

    // add states to the new min_dfa
    for (unsigned int i = 1; i <= partition_count; ++i) {
        auto *dummy = new State();
        dummy->set_state_id(i);
        dfa->insert_state(dummy);
        for (auto &state: this->old_state_mapper) {
            if (state.second == i) {
                if (state.first->is_input_state()) {
                    dummy->set_input_state(true);
                    this->dfa->set_start_state(dummy);
                }
                if (state.first->is_accept_state()) {
                    dummy->set_accept_state(true);
                    // TODO : set token type in accepting state according to priority
                    if (state.first->get_token_type().length())
                        dummy->set_token_type(state.first->get_token_type());
                }
            }
        }
        this->new_state_mapper[i] = dummy;
    }

    // add transitions to each state
    for (auto &state_id: min_state) {
        State *cur = this->new_state_mapper.at(state_id);
        for (auto &input: this->language_chars) {
            State *next_state = this->new_state_mapper[this->transition_table[make_pair(state_id, input)]];
            cur->set_transition(next_state, input);
        }
    }

    // release old dfa pointers
    for (auto &old_state: this->old_state_mapper) {
        delete (old_state.first);
    }
}