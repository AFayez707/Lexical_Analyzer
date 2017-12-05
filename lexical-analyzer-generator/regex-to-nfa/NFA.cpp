#include "NFA.h"
#include <stack>

NFA::NFA() {
    start = new State();
    end = new State();
    start->add_epsilon_transition(end);

    // add the new states to the states map
    add_state_to_map(start);
    add_state_to_map(end);
}

NFA::NFA(char c) {
    start = new State();
    end = new State();
    start->add_transition(c, end);

    // add the new states to the states map
    add_state_to_map(start);
    add_state_to_map(end);
}

void NFA::kleene_closure() {
    State *newStart = new State();
    State *newEnd = new State();

    // add the new states to the states map
    add_state_to_map(newStart);
    add_state_to_map(newEnd);

    // Thompson Construction inductive steps
    newStart->add_epsilon_transition(this->start);
    this->end->add_epsilon_transition(newEnd);
    this->end->add_epsilon_transition(this->start);
    newStart->add_epsilon_transition(newEnd);

    this->start = newStart;
    this->end = newEnd;
}

void NFA::positive_closure() {
    // Thompson Construction inductive steps
    this->end->add_epsilon_transition(this->start);

}

void NFA::concatenate(NFA *n) {
    // Thompson Construction inductive steps
    this->end->add_epsilon_transition(n->start);

    this->end = n->end;

    // merge the state maps of the two NFAs
    states.insert(n->states.begin(), n->states.end());
}

void NFA::alternate(NFA *n) {
    State *newStart = new State();
    State *newEnd = new State();

    // add the new states to the states map
    add_state_to_map(newStart);
    add_state_to_map(newEnd);

    // merge the state maps of the two NFAs
    states.insert(n->states.begin(), n->states.end());

    // Thompson Construction inductive steps
    newStart->add_epsilon_transition(this->start);
    newStart->add_epsilon_transition(n->start);

    this->end->add_epsilon_transition(newEnd);
    n->end->add_epsilon_transition(newEnd);

    this->start = newStart;
    this->end = newEnd;

    // merge the state maps of the two NFAs
    states.insert(n->states.begin(), n->states.end());
}

void NFA::add_state_to_map(State *state) {
    states[state->get_id()] = state;
}

State *NFA::get_state_by_id(int id) {
    if (states.find(id) == states.end()) // not found
        return nullptr;
    else
        return states[id];
}

/**
 * Implements the algorithm in the book
 */
set<int> NFA::epsilon_closure(set<int> state_ids) {
    stack<int> s;

    set<int> eps_closure;

    // push all states of T onto stack
    for (auto element : state_ids)
        s.push(element);

    // initialize epsilon closure to T
    for (auto element : state_ids)
        eps_closure.insert(element);

    while (!s.empty()) {
        int top = s.top();
        s.pop();
        State *top_state = this->get_state_by_id(top);

        // for each state u with an edge from to to u labeled eps
        vector<State *> eps = top_state->get_epsilon_transitions();
        for (State *&ep: eps) {
            // if u is not in eps_closure
            if (eps_closure.find(ep->get_id()) == eps_closure.end()) {
                eps_closure.insert(ep->get_id());
                s.push(ep->get_id());
            }
        }
    }

    return eps_closure;
}

set<int> NFA::move(set<int> state_ids, char c) {
    set<int> move;

    for (auto element : state_ids) {
        State *s = this->get_state_by_id(element);

        State *transitions_to = s->get_transition_on(c);
        if (transitions_to != nullptr) {
            move.insert(transitions_to->get_id());
        }
    }

    return move;
}

bool NFA::is_accepting(int state_id) {
    State *s = this->get_state_by_id(state_id);
    if (s == nullptr)
        return false;

    return s->is_accept_state();
}

int NFA::get_start_state() {
    return this->start->get_id();
}

void NFA::print_dfs() {
    bool *visited = new bool[states.size() + 5];
    for (int i = 0; i < states.size() + 5; i++)
        visited[i] = false;

    cout << "starting at state with id " << start->get_id() << endl;
    dfs_util(start->get_id(), visited);
}

void NFA::dfs_util(int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    State *s;
    if (states.find(v) == states.end())
        cout << "null pointer: state with id " << v << " is not in this NFA";
    s = states[v];

    for (int c = 'a'; c <= 'd'; c++) {
        State *next = s->get_transition_on(c);
        if (next != nullptr && !visited[next->get_id()])
            dfs_util(next->get_id(), visited);
    }

    for (auto element : s->get_epsilon_transitions())
        if (!visited[element->get_id()])
            dfs_util(element->get_id(), visited);
}

void NFA::set_accept_token_name(string token_name) {
    end->set_accept_state(std::move(token_name));
}

void NFA::combine(vector<NFA *> list_of_nfa) {
    State *newStart = new State();

    // make this NFA have the highest priority
    this->end->set_priority(0);
    newStart->add_epsilon_transition(this->start);

    int priority = 1;
    for (auto nfa : list_of_nfa) {
        newStart->add_epsilon_transition(nfa->start);
        nfa->end->set_priority(priority);
        priority++;

        // merge the state maps of the two NFAs
        states.insert(nfa->states.begin(), nfa->states.end());
    }

    this->start = newStart;
    add_state_to_map(newStart);
}

string NFA::get_accepting_token_name(int state_id) {
    State *s = this->get_state_by_id(state_id);
    if (s == nullptr)
        return "";
    return s->get_token_name();
}
