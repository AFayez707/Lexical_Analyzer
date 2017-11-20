//
// Created by abdelrahman on 18/11/17.
//

#ifndef LEXICAL_ANALYZER_CONSTRUCT_NFA_H
#define LEXICAL_ANALYZER_CONSTRUCT_NFA_H

#include "NFA.h"

bool is_input(char c);

NFA *regex_to_nfa(std::string regex);

#endif //LEXICAL_ANALYZER_CONSTRUCT_NFA_H
