//
// Created by ahmed on 11/14/17.
//

#ifndef LEXICAL_ANALYZER_DFA_REDUCER_H
#define LEXICAL_ANALYZER_DFA_REDUCER_H

#include "../graph/Graph.h"

class DFA_Reducer {
public:
    explicit DFA_Reducer(Graph *dfa, set<char> language_chars);

    Graph *get_dfa() const;

    /**
     * @brief magic inside, WARNING: DO NOT TOUCH !! (Unless you are Mr. Robot)
     */
    void minimize();

    void print();

private:
    Graph *dfa;
    set<char> language_chars;
    map<int, State *> new_state_mapper;
    map<State *, int> old_state_mapper;
    map<pair<int, char>, int> transition_table;

    /**
     * @brief deletes all redundant states
     */
    void remove_redundancies();

    void replace_redundant(State *A, State *B);

    /**
     * @brief run's hopcroft minimizing algorithm, and maps every dfa state to a state in the minimized dfa
     * @return partitions count
     */
    int merge_non_distinguishable();

    /**
     * @brief creates transition table, then the minimized dfa
     */
    void build_min_dfa(int partition_count);
};

#endif //LEXICAL_ANALYZER_DFA_REDUCER_H
