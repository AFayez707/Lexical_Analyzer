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

    void display();

    void simulate(string source_code);

private:
    Graph *dfa;
    set<char> language_chars;
    map<int, State *> new_state_mapper;
    map<State *, int> old_state_mapper;
    map<pair<int, char>, int> transition_table;

    /**
     * @brief merging the non-distinguishable states of a DFA, due to Hop-croft algorithm, is based on partition refinement,
     * partitioning the DFA states into groups by their behavior.
     * Whereby every two states of the same partition are equivalent if they have the same behavior for all the input sequences.
     * @return partitions count
     */
    int merge_non_distinguishable();

    /**
     * @brief creates transition table, then the minimized dfa
     */
    void build_minimized_dfa(int partition_count);
};

#endif //LEXICAL_ANALYZER_DFA_REDUCER_H
