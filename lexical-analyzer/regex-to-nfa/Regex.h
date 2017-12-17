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
    set<char> language_characters;
    vector<pair<string, string>> expressions;

    Regex(string path, ofstream *log_file);

    void parse();

private:
    string path;
    ofstream *log_file;

    int Precedence(char symbol);

    map<string, string> InToPost(map<string, string> exp);

    map<string, string> InsertConcatenate(map<string, string> exp);
};

#endif //LEXICAL_ANALYZER_REGEX_H
