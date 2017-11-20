//
// Created by abdelrahman on 13/11/17.
//

#include "Regex.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;


Regex::Regex(std::string file_path) {
    path = file_path;
}

std::unordered_map<std::string, std::string> Regex::parse(path) {
    unordered_map<std::string, std::string> ExpMap;  //Expressions Map >> Returned
    unordered_map<std::string, std::string> DefMap;  //Definitions Map >> Only Used Here to replace definitions
    ifstream infile("/Users/macpro/Documents/Term7/project/file.txt");
    string line, exp_name, expression, temp, keyword, punctuation;
    char low_letter = 'a', up_Letter = 'A', num = '0';

    while (std::getline(infile, line)) {
        // Function on line

        int i = 0;

        // skip white spaces in the beggining of the file
        while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
            i++;

        //build exp_name
        if (i < line.length() && line[i] == '{') {
            i++;
            while (i < line.length() && line[i] != '}') {
                while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                    i++;
                if (line[i] == '}')
                    break;
                while (i < line.length() && isalpha(line[i])) {
                    keyword = string(keyword + line[i]);
                    i++;
                }
                if (ExpMap.find(keyword) == ExpMap.end())
                    ExpMap.insert({keyword, keyword});
                keyword.clear();
            }
        } else if (i < line.length() && line[i] == '[') {
            i++;
            while (i < line.length() && line[i] != ']') {
                while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                    i++;
                punctuation = string(punctuation + line[i]);
                if (line[i] != 92)
                    punctuation = string(punctuation + '|');
                i++;
            }
            punctuation.pop_back();
            ExpMap.insert({"punctuation", punctuation});
            punctuation.clear();
        } else {
            while (i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] != '=' && line[i] != ':')
                exp_name = string(exp_name + line[i++]);

            // skip white spaces after exp name
            while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                i++;

            if (i < line.length() && line[i] == '=') {
                i++;
                while (i < line.length()) {
                    // skip white spaces
                    while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                        i++;

                    if (i < line.length() && (line[i] == 'a' && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        expression = string(expression + '(');
                        for (int j = 0; j < 26; j++)
                            expression = string(expression + (low_letter++) + '|');
                        expression.pop_back();
                        expression = string(expression + ')');
                        while (line[i] != 'z')
                            i++;
                        i++;
                    } else if (i < line.length() && (line[i] == 'A' && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        expression = string(expression + '(');
                        for (int j = 0; j < 26; j++)
                            expression = string(expression + (up_Letter++) + '|');
                        expression.pop_back();
                        expression = string(expression + ')');
                        while (line[i] != 'Z')
                            i++;
                        i++;
                    } else if (i < line.length() && (line[i] == '0' && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        expression = string(expression + '(');
                        for (int j = 0; j < 10; j++)
                            expression = string(expression + (num++) + '|');
                        expression.pop_back();
                        expression = string(expression + ')');
                        while (line[i] != '9')
                            i++;
                        i++;
                    } else if (i < line.length() &&
                               (line[i] == '(' || line[i] == ')' || line[i] == '*' || line[i] == '+' ||
                                line[i] == '|')) {
                        expression = string(expression + line[i]);
                        i++;
                    } else {     // word is already in the DefMap
                        while (i < line.length() && isalpha(line[i])) {
                            temp = string(temp + line[i]);
                            i++;
                        }
                        if (DefMap.find(temp) != DefMap.end()) {
                            string value = DefMap[temp];
                            expression = string(expression + value);
                        }
                    }
                    temp.clear();
                }
                if(expression[0] == '(' && expression[expression.length() - 1] == ')' &&
                   expression.find(")|(") != std::string::npos){
                    expression.push_back(')');
                    expression.insert(0,1,'(');
                }

                DefMap.insert({exp_name, expression});
                exp_name.clear();
                expression.clear();
            }

            if (i < line.length() && line[i] == ':') {
                i++;
                while (i < line.length()) {
                    while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                        i++;
                    if (i < line.length() && (line[i] == '(' || line[i] == ')' || line[i] == '*' || line[i] == '+' ||
                                              line[i] == '|')) {
                        expression = string(expression + line[i]);
                        i++;
                    } else if (i < line.length() && isalpha(line[i])) {
                        while (i < line.length() && isalpha(line[i])) {
                            temp = string(temp + line[i]);
                            i++;
                        }
                        if (DefMap.find(temp) != DefMap.end()) {
                            string value = DefMap[temp];
                            expression = string(expression + value);
                        } else {
                            expression = string(expression + temp);
                        }
                    } else {
                        if (line[i] == '.')
                            expression = string(expression + '\\');
                        expression = string(expression + line[i]);
                        i++;
                    }
                    temp.clear();
                }
                ExpMap.insert({exp_name, expression});
                exp_name.clear();
                expression.clear();
            }

        }
        // now we loop back and get the next line in 'Line'
    }
    Regex::InsertConcatenation(ExpMap);
    return ExpMap;
}


void Regex::InsertConcatenation(unordered_map<std::string, std::string> ExpMap){
    for (auto it = ExpMap.begin(); it != ExpMap.end(); ++it) {
        string exp = it->second;

        int i = 0, j, len = exp.length();
        while (exp[i + 1] != '\0') {
            if ((((exp[i] != '('  && exp[i] != '|' && exp[i] != '\\')
                  || exp[i] == ')'
                  || exp[i] == '*'
                  || exp[i] == '+')
                 &&
                 (exp[i + 1] != ')' && exp[i + 1] != '.' && exp[i + 1] != '|' && exp[i + 1] != '*' && exp[i + 1] != '+'))) {
                exp = string(exp + ' ');
                for (j = len+1; j > i + 1; j--) {
                    exp[j] = exp[j - 1];
                }
                exp[i + 1] = '.';
                len++;
                exp[len] = '\0';
                i++;
            }
            i++;
        }
        it->second = exp;
    }
}





std::set<char> Regex::get_language() {

}
