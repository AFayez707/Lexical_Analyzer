//
// Created by abdelrahman on 13/11/17.
//


#include <stack>
#include "NFA.h"


bool is_input(char c) {
    return !(c == '(' || c == ')' || c == '*' || c == '+' || c == '.');
}

/**
 * takes in a regex in postfix notation containing only "( ) | * +"
 * and constructs an nfa that accepts only the strings that match the given RE
 */
NFA *regex_to_nfa(string regex) {
    stack<NFA *> operands;

    bool escape = false;

    for (int i = 0; i < regex.size(); i++) {
        char c = regex[i];

        if (escape) {
            // treat the current char as if it is a normal letter
            NFA *single_character;
            if(c == 'L')
                single_character =  new NFA();
            else
                single_character = new NFA(c);

            operands.push(single_character);

            escape = false;
            continue;
        }

        if (c == '\\') {
            escape = true;
            continue;
        }

        NFA *first;
        NFA *second;
        NFA *top;
        switch (c) {
            case '.':
                second = operands.top();
                operands.pop();
                first = operands.top();
                operands.pop();
                first->concatenate(second);
                operands.push(first);
                break;
            case '*':
                top = operands.top();
                operands.pop();
                top->kleene_closure();
                operands.push(top);
                break;
            case '+':
                top = operands.top();
                operands.pop();
                top->positive_closure();
                operands.push(top);
                break;
            case '|':
                second = operands.top();
                operands.pop();
                first = operands.top();
                operands.pop();
                first->alternate(second);
                operands.push(first);
                break;
            default: // input language
                // create a new NFA that accepts only this character ("c")
                NFA *single_character = new NFA(c);
                operands.push(single_character);
                break;
        }

    }

    NFA *result = operands.top();
    operands.pop();

    // sanity check (if stack is not empty now then the input regex was invalid)
    if (operands.size() != 0) {
        // error
        return nullptr;
    }

    return result;
}


NFA *language_to_nfa(vector<pair<string, string>> regexes) {
    if (regexes.empty())
        return nullptr;

    vector<NFA *> NFAs;

    for (pair<string, string> regex : regexes) {
        NFA *nfa = regex_to_nfa(regex.second);

        nfa->set_accept_token_name(regex.first);

        NFAs.push_back(nfa);
    }

    NFA *first_nfa = NFAs[0];

    // remove the first element
    NFAs.erase(NFAs.begin());

    first_nfa->combine(NFAs);

    return first_nfa;
}