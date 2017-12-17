//
// Created by ahmed on 11/14/17.
//

#include "DFA_Reducer.h"
#include <fstream>
#include <iomanip>

DFA_Reducer::DFA_Reducer(Graph *dfa, set<char> language_chars) {
    this->dfa = dfa;
    this->language_chars = std::move(language_chars);
}

Graph *DFA_Reducer::get_dfa() const {
    return this->dfa;
}

void DFA_Reducer::minimize() {
    int partition_count = this->merge_non_distinguishable();
    this->build_minimized_dfa(partition_count);
}

void DFA_Reducer::log(ofstream *log_file) {
    *log_file << "\n\n\nMinimized DFA:\n";

    set<State *> states = this->dfa->get_states();
    string line = "-----------------------------";
    for (unsigned int i = 0; i < language_chars.size(); ++i)
        line += "-------";

    *log_file << line << "\n                              ";
    for (auto &input: this->language_chars)
        *log_file << "| " << setw(5) << input;

    *log_file << "\n" << line << "\n";
    for (auto &state: states) {
        if (state->is_input_state())
            *log_file << " ➜ |";
        else
            *log_file << "   |";

        if (state->is_accept_state())
            *log_file << " " << setw(12) << state->get_token_name() << " |";
        else
            *log_file << "              |";

        *log_file << setw(5) << state->get_id() << "  =>  ";
        for (auto &next_state: state->get_transitions())
            *log_file << "| " << setw(5) << next_state.second->get_id();
        *log_file << endl;
    }
    *log_file << line << endl;
    log_file->flush();
}

int DFA_Reducer::merge_non_distinguishable() {
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

    bool flag = true;
    while (flag) {
        flag = false;
        // loop all partitions
        for (auto &partition: disjoint_set) {
            // loop all states in the same partitions
            set<State *> partition_states = partition.second;

            for (auto &stateA: partition_states) {
                set<State *> cur_set;
                cur_set.insert(stateA);
                for (auto &stateB: partition_states) {
                    if (stateA == stateB) continue;

                    bool may_match = (stateA->is_input_state() == stateB->is_input_state());
                    may_match = may_match && (stateA->is_accept_state() == stateB->is_accept_state());
                    may_match = may_match && (stateA->get_token_name() == stateB->get_token_name());
                    if (!may_match) continue;

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
                    if (in_same_set)
                        cur_set.insert(stateB);
                }
                // if this partitions needs minimization
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
                    }
                    // update current partition with remaining states
                    disjoint_set[partition.first] = partition_states;
                    break;
                }
            }
            if (flag) break;
        }
    }
    return partition_count;
}

void DFA_Reducer::build_minimized_dfa(int partition_count) {
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
    for (int i = 1; i <= partition_count; ++i) {
        auto *dummy = new State();
        dummy->set_id((unsigned int) i);
        dfa->insert_state(dummy);
        for (auto &state: this->old_state_mapper) {
            if (state.second == i) {
                if (state.first->is_input_state()) {
                    dummy->set_input_state(true);
                    this->dfa->set_start_state(dummy);
                }
                if (state.first->is_accept_state()) {
                    // if this state priority > current priority, set token name to the highest priority
                    if (state.first->get_priority() > dummy->get_priority())
                        dummy->set_accept_state(state.first->get_token_name());
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
    for (auto &old_state: this->old_state_mapper)
        delete (old_state.first);
}

void DFA_Reducer::tokenize(string file_path) {
    ifstream file(file_path, ios_base::in);
    string source_code;

    while (true) {
        int c = file.get();
        if (c == EOF) {
            this->tokenizer(source_code);
            break;
        }
        if (c == ' ' || c == '\t' || c == '\n') {
            if (!source_code.empty()) {
                this->tokenizer(source_code);
                source_code = "";
            }
            continue;
        }
        source_code.push_back((char) c);
    }
    file.close();
}

void DFA_Reducer::tokenizer(string source_code) {
    unsigned int start = 0, end = 0;
    unsigned int lexeme_end = 0;
    string token, lexeme;
    State *cur_state = this->dfa->get_start_state();

    // space is the end of string flag
    source_code.push_back(' ');
    while (start != source_code.size() - 1) {
        char c = source_code[end];

        // if this char is not in the language chars && not end of string
        if (this->language_chars.find(c) == this->language_chars.end() && c != ' ') {
            source_code.erase(end, 1);
            printf("lexical_error: unknown character \'%c\'\n", c);
            continue;
        }

        end++;
        // if reached end of string, return the longest token found
        if (start < end && end == source_code.size()) {
            lexeme = source_code.substr(start, lexeme_end - start);
            if (lexeme.empty()) {
                printf("lexical_error: can match any token starting with => \'%c\'\n", source_code[start]);
                exit(1);
            } else {
                tokens.push(make_pair(lexeme, token));
                printf("%-20s =>    %s\n", token.c_str(), lexeme.c_str());
                end = start = lexeme_end;
                cur_state = this->dfa->get_start_state();
                continue;
            }
        }

        cur_state = cur_state->get_transition_on(c);
        if (cur_state->is_accept_state()) {
            token = cur_state->get_token_name();
            lexeme_end = end;
        }
    }
}
