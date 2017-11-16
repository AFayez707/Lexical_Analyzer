//
// Created by ahmed on 11/13/17.
//

#ifndef LEXICAL_ANALYZER_STATE_H
#define LEXICAL_ANALYZER_STATE_H

#include <vector>
#include <map>

using namespace std;

class State {
public:
    State();

    bool is_accept_state() const;

    void set_accept_state(bool is_accept_state);

    int get_state_id() const;

    void set_state_id(unsigned int id);

    void set_transition(State *next, string input);

    State *get_transition_on(string input);

    void set_epsilon_transition(State *state);

    vector<State *> get_epsilon_transitions() const;

    map<string, State *> get_transitions() const;

    string get_token_type() const;

    void set_token_type(string token_type);

    bool is_input_state() const;

    void set_input_state(bool input_state);

private:
    static unsigned int state_count;
    unsigned int state_id = 0;
    bool accept_state = false;
    bool input_state = false;
    string token_type = "";
    vector<State *> epsilon_transitions;
    map<string, State *> transitions;
};

#endif //LEXICAL_ANALYZER_STATE_H
