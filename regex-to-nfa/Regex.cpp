//
// Created by abdelrahman on 13/11/17.
//

#include "Regex.h"
#include <iostream>


Regex::Regex(std::string file_path) {
    path = file_path;
}

std::unordered_map<std::string, std::string> Regex::parse() {
    std::cout << path;
}

std::vector<char> Regex::get_language() {

}
