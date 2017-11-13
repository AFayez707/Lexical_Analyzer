//
// Created by abdelrahman on 12/11/17.
//

#ifndef LEXICAL_ANALYZER_NFASTATE_H
#define LEXICAL_ANALYZER_NFASTATE_H


class NFAState {
public:
    NFAState();
    bool is_accepting();
    int get_id();
    NFAState transitionOn(char c);

private:
    int id;

};


#endif //LEXICAL_ANALYZER_NFASTATE_H
