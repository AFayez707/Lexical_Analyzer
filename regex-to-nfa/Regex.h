//
// Created by abdelrahman on 13/11/17.
//

#ifndef LEXICAL_ANALYZER_REGEX_H
#define LEXICAL_ANALYZER_REGEX_H

#include "LinkedStack.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

class Regex {
public:
    Regex(std::string path);
    std::unordered_map<std::string, std::string> parse();
    std::set<char> get_language();
    void Regex::InsertConcatenation(unordered_map<std::string, std::string> ExpMap);
    void RegExpToPost();

private:
    std::string path;
    char *exp;
    char *post;
    int Precedence(char symbol);
};

#endif //LEXICAL_ANALYZER_REGEX_H
