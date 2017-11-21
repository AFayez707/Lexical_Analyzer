//
// Created by H.H.H on 20/11/17.
//

#ifndef LEXICAL_ANALYZER_REGEX_H
#define LEXICAL_ANALYZER_REGEX_H

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Regex {
public:
    explicit Regex(string path);


    void parse2();

    set<char> language_characters;
    vector<pair<string, string>> expressions;

private:
    vector<string> expression_names;

    string path;

    int Precedence(char symbol);
};

#endif //LEXICAL_ANALYZER_REGEX_H
