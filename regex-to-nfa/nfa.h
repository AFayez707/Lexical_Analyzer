#ifndef LEXICAL_ANALYZER_NFA_H
#define LEXICAL_ANALYZER_NFA_H

#include <iostream>
#include <set>
#include "NFAState.h"

using namespace std;

class nfa {
private:

public:
    /**
     * creates an nfa that accepts only the character c
     */
    nfa(char c);

    void kleene_closure();

    void positive_closure();

    /**
     * concatenates this NFA with n by creating an NFA that accepts the concatenation set of
     * strings accepted by this and the set of strings accepted by n.
     */
    void concatenate(nfa* n);

    void alternate(nfa* n);

    /**
     * combines this nfa with each nfa in list_of_nfa and gives accepting priority according
     * to the order or nfa in the list_of_nfa. an nfa that is earlier in the list has higher
     * priority than an nfa after it and this nfa will has the highest priority. This is essentially equivalent to calling
     * alternate on this and each nfa in the list_of_nfa, except that combine doesn't combine
     * the end states into one accepting state. This method should be called when an nfa has
     * been constructed for each regular expression a language and a single nfa for the
     * language is required.*/
    void combine(vector<nfa*> list_of_nfa);

    // void existance(nfa n); // set to name of question mark operator

    set<int> epsilon_closure(set<int> state_ids);

    set<int> move(set<int> state_ids, char c);

    bool is_accepting(int state_id);
    string get_accepting_token_name(int state_id);

    int get_start_state();

    /**
     * sets the end state of this nfa as an accepting state and sets the end state accepting
     * name to be token_name. It essentially gives this nfa a name which is the name of
     * the token it accepts
     */
    void set_accept_token_name(string token_name);

    void print_dfs();

private:
    NFAState* start;
    NFAState* end;
    unordered_map<int, NFAState*> states;
    void add_state_to_map(NFAState* state);
    NFAState* get_state_by_id(int id);



    void dfs_util(int v, bool *visited);
};

#endif //LEXICAL_ANALYZER_NFA_H
