//
// Created by abdelrahman on 13/11/17.
//


#include <stack>
#include "nfa.h"


bool isInput(char c) {
    return ! (c == '(' || c == ')' || c == '*' || c == '+' || c == '.');
}


/**
 * takes in a regex in postfix notation containing only "( ) | * +"
 * and constructs an nfa that accepts only the strings that match the given RE
 */
nfa* regex_to_nfa(std:: string regex) {
    stack<nfa*> operands;

    for(int i = 0; i < regex.size(); i++) {
        char c = regex[i];

        nfa *first;
        nfa *second;
        nfa *top;
        switch(c) {
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
                // create a new nfa that accepts only this character ("c")
                nfa* single_character = new nfa(c);
                operands.push(single_character);
                break;
        }

        nfa *result = operands.top();
        operands.pop();

        // sanity check (if stack is not empty now then the input regex was invalid)
        if(operands.size() != 0) {
            // error
            return 0;
        }

        return result;
    }

}