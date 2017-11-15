//
// Created by ahmed on 11/14/17.
//

#ifndef LEXICAL_ANALYZER_DFA_REDUCER_H
#define LEXICAL_ANALYZER_DFA_REDUCER_H

#include "../graph/Graph.h"

class DFA_Reducer {
public:
    explicit DFA_Reducer(Graph *dfa);

    Graph *get_dfa();

    Graph *remove_redundancies();

    Graph *minimize();

private:
    Graph *dfa;
};

#endif //LEXICAL_ANALYZER_DFA_REDUCER_H
