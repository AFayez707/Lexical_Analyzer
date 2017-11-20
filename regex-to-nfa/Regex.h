//
// Created by abdelrahman on 13/11/17.
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

    void insert_concatenation(map<string, string> ExpMap);

    void reg_exp_to_post(map<string, string> ExpMap);

private:
    string path;

    int precedence(char symbol);
};

#endif //LEXICAL_ANALYZER_REGEX_H
