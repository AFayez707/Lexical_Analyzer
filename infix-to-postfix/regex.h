//
// Created by MacPro on 11/14/17.
//

#ifndef LEXICAL_ANALYZER_REGEX_H
#define LEXICAL_ANALYZER_REGEX_H

#include "LinkedStack.h"
#include <string>
using namespace std;

// Define the class of regex
class regex
{
public:
    void GetRegExp();
    void InsertCatNode();
    void RegExpToPost();

private:
    char *exp;
    char *post;
    int Precedence(char symbol);
};

#endif //LEXICAL_ANALYZER_REGEX_H
