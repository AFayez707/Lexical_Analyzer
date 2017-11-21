//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_STATE_H
#define LEXICAL_ANALYZER_STATE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class State {
public:
    State();

    bool is_accept_state() const;

    void set_accept_state(string token_name);

    int get_id() const;

    void set_id(unsigned int id);

    void add_transition(char input, State *next);

    State *get_transition_on(char input);

    void add_epsilon_transition(State *state);

    vector<State *> get_epsilon_transitions() const;

    map<char, State *> get_transitions() const;

    string get_token_name() const;

    void set_token_name(string token_name);

    bool is_input_state() const;

    void set_input_state(bool input_state);

    void set_priority(int priority);

    int get_priority();

private:
    static unsigned int state_count;
    unsigned int id = 0;
    int priority = -1;
    bool input_state = false;
    string token_name = "undefined";
    vector<State *> epsilon_transitions;
    map<char, State *> transitions;
};

#endif //LEXICAL_ANALYZER_STATE_H
