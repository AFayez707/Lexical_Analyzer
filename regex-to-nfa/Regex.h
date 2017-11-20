//
// Created by H.H.H on 20/11/17.
//

#ifndef LEXICAL_ANALYZER_REGEX_H
#define LEXICAL_ANALYZER_REGEX_H

#include <map>
#include <set>
#include <string>

using namespace std;

class Regex {
public:
    explicit Regex(string path);

    map<string, string> parse();

    set<char> get_language();



private:
    string path;
    set<char> language_characters;

    int precedence(char symbol);

    void insert_concatenation(map<string, string> ExpMap);

    void reg_exp_to_post(map<string, string> ExpMap);
};

#endif //LEXICAL_ANALYZER_REGEX_H
