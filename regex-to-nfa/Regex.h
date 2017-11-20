//
// Created by abdelrahman on 13/11/17.
//

#ifndef LEXICAL_ANALYZER_REGEX_H
#define LEXICAL_ANALYZER_REGEX_H

#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

class Regex {
public:
    Regex(std::string path);

    std::unordered_map<std::string, std::string> parse();

    std::vector<char> get_language();

private:
    std::string path;
};

#endif //LEXICAL_ANALYZER_REGEX_H
