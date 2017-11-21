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
    printf("\n\nMinimizing DFA:\n\n");
    // removes redundancies
//    this->remove_redundancies();

    // merging states using disjoint sets
    int partition_count = this->merge_non_distinguishable();
    this->build_min_dfa(partition_count);
}

void DFA_Reducer::print() {
    set<State *> states = this->dfa->get_states();

    string line = "---------------";
    for (int i = 0; i < language_chars.size(); ++i)
        line += "-------";

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

        printf("%5d  =>  ", state->get_id());
        for (auto &next_state: state->get_transitions()) {
            printf("| %-5d", next_state.second->get_id());
        }
        printf("\n");
    }
    printf("%s\n", line.c_str());
}

//void DFA_Reducer::remove_redundancies() {
//    printf("1- Eliminating redundancies\n============================\n");
//    set<State *> states = dfa->get_states();
//    map<State *, State *> redundant;
//    set<State *> updated;
//
//    for (auto &A: states) {
//        if (updated.find(A) != updated.end()) continue;
//        for (auto &B: states) {
//            if (A == B || updated.find(B) != updated.end()) continue;
//
//            // Two states are equivalent if => `input & accept & token_name & transitions` are equal
//            bool condition = A->get_transitions().size() == B->get_transitions().size();
//            condition = condition && (A->is_accept_state() == B->is_accept_state());
//            condition = condition && (A->get_token_name() == B->get_token_name());
//            condition = condition && (A->is_input_state() == B->is_input_state());
//
//            if (condition) {
//                bool valid = true;
//
//                // Match all transitions on both states
//                for (char c: this->language_chars) {
//                    State *tran_a = A->get_transition_on(c);
//                    State *tran_b = B->get_transition_on(c);
//                    if (tran_a != tran_b) {
//                        valid = false;
//                        break;
//                    }
//                }
//
//                if (valid) {
//                    // Replace redundancies in the states set
//                    printf("Redundant: %-3d ==> %3d\n", A->get_id(), B->get_id());
//                    this->replace_redundant(A, B);
//                    updated.insert(B);
//                }
//            }
//        }
//    }
//
//    for (auto state: updated) {
//        this->dfa->erase_state(state);
//    }
//}

//void DFA_Reducer::replace_redundant(State *A, State *B) {
//    for (auto &state: this->dfa->get_states()) {
//        for (auto &next_state: state->get_transitions()) {
//            if (next_state.second == B) {
//                state->add_transition(next_state.first, A);
//            }
//        }
//    }
//}

int DFA_Reducer::merge_non_distinguishable() {
    printf("\n2- Merging non-distinguishable states\n=====================================\n");
    int partition_count = 2; // starting with two partitions accept states & non-accept states
    map<int, set<State *> > disjoint_set;

    // Create initial two sets, accepting and non-accepting states
    for (auto &state: this->get_dfa()->get_states()) {
        if (state->is_accept_state()) {
            disjoint_set[1].insert(state);
            this->old_state_mapper[state] = 1;
        } else {
            disjoint_set[2].insert(state);
            this->old_state_mapper[state] = 2;
        }
    }

    set<State *> minimized_states;
    bool flag = true;
    while (flag) {
        flag = false;
        // loop all partitions
        for (auto &partition: disjoint_set) {
            // loop all states in the same partitions
            set<State *> partition_states = partition.second;
            if (partition_states.size() < 2) continue;

            for (auto &stateA: partition_states) {
//                if (minimized_states.find(stateA) != minimized_states.end())
//                    continue;
                set<State *> cur_set;
                cur_set.insert(stateA);
                for (auto &stateB: partition_states) {
                    if (stateA == stateB) continue;
                    bool may_be = true;
                    may_be = may_be && (stateA->is_input_state() == stateB->is_input_state());
                    may_be = may_be && (stateA->is_accept_state() == stateB->is_accept_state());
                    may_be = may_be && (stateA->get_token_name() == stateB->get_token_name());
                    if (may_be)
                        continue;
//                    if (stateA == stateB || minimized_states.find(stateB) != minimized_states.end())
//                        continue;
                    bool in_same_set = true;
                    for (char c: this->language_chars) {
                        State *a_on_c = stateA->get_transition_on(c);
                        State *b_on_c = stateB->get_transition_on(c);
                        if (old_state_mapper[a_on_c] != old_state_mapper[b_on_c]) {
                            in_same_set = false;
                            break;
                        }
                    }
                    // if stateA matches stateB for each char c
                    if (in_same_set) {
                        cur_set.insert(stateB);
                    }
                }
                // this partitions is not minimized
                if (cur_set.size() != partition_states.size()) {
                    // this partitions is split
                    flag = true;

                    partition_count++;
                    // insert new partition
                    disjoint_set[partition_count] = cur_set;
                    // loop all the states of new set and move to new partitions
                    for (auto &state: cur_set) {
                        partition_states.erase(state);
                        old_state_mapper[state] = partition_count;
                        minimized_states.insert(state);
                    }
                    disjoint_set[partition.first] = partition_states;
                    break;
                }
            }
            if (flag)
                break;
        }
    }
    return partition_count;
}

void DFA_Reducer::build_min_dfa(int partition_count) {
    set<int> min_states;

    // Form transition_table table
    for (auto &state: this->old_state_mapper) {
        min_states.insert(state.second);
        for (auto &move: state.first->get_transitions()) {
            pair<int, char> cur_pair = make_pair(this->old_state_mapper[state.first], move.first);
            this->transition_table[cur_pair] = this->old_state_mapper[move.second];
        }
    }

    // Building new min_dfa
    delete (this->dfa);
    this->dfa = new Graph();

    // Add states to the new min_dfa
    for (unsigned int i = 1; i <= partition_count; ++i) {
        auto *dummy = new State();
        dummy->set_id(i);
        dfa->insert_state(dummy);
        for (auto &state: this->old_state_mapper) {
            if (state.second == i) {
                if (state.first->is_input_state()) {
                    dummy->set_input_state(true);
                    this->dfa->set_start_state(dummy);
                }
                if (state.first->is_accept_state()) {
                    dummy->set_accept_state(state.first->get_token_name());
                    // TODO: (in case of overlapping accept states)
                    // TODO: set token type in accepting state according to priority
                }
            }
        }
        this->new_state_mapper[i] = dummy;
    }

    // Add transitions to each state
    for (auto &state_id: min_states) {
        State *cur = this->new_state_mapper.at(state_id);
        for (auto &input: this->language_chars) {
            State *next_state = this->new_state_mapper[this->transition_table[make_pair(state_id, input)]];
            cur->add_transition(input, next_state);
        }
    }

    // Release old DFA pointers
    for (auto &old_state: this->old_state_mapper) {
        delete (old_state.first);
    }
}

void DFA_Reducer::simulate(string source_code) {
    State *current_state1 = this->dfa->get_start_state();
    int lexem_start = 0;
    int lexeme_end = 0;
    State *last_accepting_lexem;
    int last_accepting_lexeme_end = 0;
    State *last_accepting_state1;
    int last_accepting_state = -1;

    source_code.push_back(' ');

    while (lexem_start < source_code.size() && lexeme_end < source_code.size()) {
        char c = source_code[lexeme_end];

        if (current_state1->is_accept_state()) {
            last_accepting_state1 = current_state1;
            last_accepting_lexeme_end = lexeme_end;
        }

        current_state1 = current_state1->get_transition_on(c);
        if(current_state1 == nullptr && (c != ' ' && c != '\t' && c != '\n')) {
            printf("Syntax Error: unknown character: \'%c\'\n", c);
            exit(1);
        }
        lexeme_end++;

        if (lexeme_end == source_code.size() && lexem_start < source_code.size()) {
            if (lexem_start == source_code.size() - 1) {
                return;
            }
            if (lexem_start == last_accepting_lexeme_end) {
                printf("Couldn't detect any accepting token\n");
                exit(1);
            } else {
                string token = source_code.substr(lexem_start, last_accepting_lexeme_end - lexem_start);

                printf("Found token: * %-10s *  ===>  %-10s\n", token.c_str(),
                       last_accepting_state1->get_token_name().c_str());

                lexem_start = last_accepting_lexeme_end;
                lexeme_end = lexem_start;
                current_state1 = this->dfa->get_start_state();
            }
        }
    }
}
