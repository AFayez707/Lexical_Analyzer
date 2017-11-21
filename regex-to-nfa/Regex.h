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

    vector< pair<string, string> > parse();

    void parse2();

    set<char> language_characters;
    vector<pair<string,string>> expressions;
    set<char> get_language();

private:
    vector<string> expression_names;

    string path;

    int Precedence(char symbol);

    void insert_concatenation(map<string, string> ExpMap);

    void reg_exp_to_post(map<string, string> ExpMap);
};

#endif //LEXICAL_ANALYZER_REGEX_H
