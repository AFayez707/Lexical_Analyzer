#include "nfa.h"
#include <stack>

nfa::nfa(char c) {
    start = new NFAState();
    end = new NFAState();
    start->set_transition_On(c, end);

    // add the new states to the states map
    add_state_to_map(start);
    add_state_to_map(end);
}

void nfa::kleene_closure() {
    NFAState *newStart = new NFAState();
    NFAState *newEnd = new NFAState();

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

void nfa::positive_closure() {
    // Thompson Construction inductive steps
    NFAState *newStart = new NFAState();
    NFAState *newEnd = new NFAState();

    // add the new states to the states map
    add_state_to_map(newStart);
    add_state_to_map(newEnd);

    newStart->add_epsilon_transition(this->start);
    this->end->add_epsilon_transition(newEnd);
    this->end->add_epsilon_transition(this->start);

    this->start = newStart;
    this->end = newEnd;
}

void nfa::concatenate(nfa *n) {
    // Thompson Construction inductive steps
    this->end->add_epsilon_transition(n->start);

    // merge the state maps of the two NFAs
    states.insert(n->states.begin(), n->states.end());
}

void nfa::alternate(nfa *n) {
    NFAState *newStart = new NFAState();
    NFAState *newEnd = new NFAState();

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
}

void nfa::add_state_to_map(NFAState *state) {
    states[state->get_id()] = state;
}

NFAState *nfa::get_state_by_id(int id) {
    if(states.find(id) == states.end()) // not found
        return nullptr;
    else
        return states[id];
}

/**
 * Implements the algorithm in the book
 */
set<int> nfa::epsilon_closure(set<int> state_ids) {
    stack<int> s;

    set<int> eps_closure;

    // push all states of T onto stack
    for(auto element : state_ids)
        s.push(element);

    // initialize epsilon closure to T
    for(auto element : state_ids)
        eps_closure.insert(element);

    while(s.size() > 0) {
        int top = s.top();
        s.pop();
        NFAState *top_state = this->get_state_by_id(top);

        // for each state u with an edge from to to u labeled eps
        vector<NFAState*> eps = top_state->get_epsilon_transitions();
        for(int i = 0; i < eps.size(); i++) {

            // if u is not in eps_closure
            if(eps_closure.find(eps[i]->get_id()) == eps_closure.end()) {
                eps_closure.insert(eps[i]->get_id());
                s.push(eps[i]->get_id());
            }
        }
    }

    return eps_closure;
}

set<int> nfa::move(set<int> state_ids, char c) {
    set<int> move;

    for(auto element : state_ids) {
        NFAState *s = this->get_state_by_id(element);

        NFAState *transitions_to = s->get_transition_On(c);
        if(transitions_to != nullptr) {
            move.insert(transitions_to->get_id());
        }
    }

    return move;
}

bool nfa::is_accepting(int state_id) {
    NFAState *s = this->get_state_by_id(state_id);
    if(s == nullptr)
        return false;

    return s->is_accepting();
}

int nfa::get_start_state() {
    return this->start->get_id();
}

void nfa::print_dfs() {
    bool *visited = new bool[states.size() + 5];
    for(int i = 0; i < states.size() + 5; i++)
        visited[i] = false;

    cout << "starting at state with id " << start->get_id() << endl;
    dfs_util(start->get_id(), visited);
}

void nfa::dfs_util(int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    NFAState *s;
    if(states.find(v) == states.end())
        cout << "null pointer: state with id " << v << " is not in this NFA";
    s = states[v];

    for(int c = 'a'; c <= 'd'; c++) {
        NFAState *next = s->get_transition_On(c);
        if(next != nullptr && !visited[next->get_id()])
            dfs_util(next->get_id(), visited);

    }
    for (auto element : s->get_epsilon_transitions())
        if (!visited[element->get_id()])
            dfs_util(element->get_id(), visited);
}

void nfa::set_accept_token_name(string token_name) {
    end->setAccepting(token_name);
}

void nfa::combine(vector<nfa *> list_of_nfa) {
    NFAState *newStart = new NFAState();

    // make this nfa have the highest priority
    this->end->setPriority(0);
    newStart->add_epsilon_transition(this->start);

    int priority = 1;
    for(auto nfa : list_of_nfa) {
        newStart->add_epsilon_transition(nfa->start);
        nfa->end->setPriority(priority);
        priority++;
    }
}
