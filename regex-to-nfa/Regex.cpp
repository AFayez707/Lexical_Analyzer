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
    ifstream infile(path);
    string line, exp_name, expression, temp;
    char low_letter = 'a', up_Letter = 'A', num = '0';

    while (std::getline(infile, line)) {
        // Function on line

        int i = 0;

        // skip white spaces in the beggining of the file
        while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
            i++;

        //build exp_name
        while (i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] != '=' && line[i] != ':')
            exp_name = string(exp_name + line[i++]);

        // skip white spaces after exp name
        while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
            i++;

        if( i < line.length() && line[i] == '=' ){
            while(i < line.length()) {
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
                } else if (i < line.length() && (line[i] == '(' || line[i] == ')' || line[i] == '*' || line[i] == '+' ||
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
            }

            DefMap.insert( { exp_name, expression });
            exp_name.clear();
            exp_name.str("");
            expression.clear();
            expression.str("");
            temp.clear();
            temp.str("");
        }

        /*if( i < line.length() && line[i] == ':' ){
            while(i < line.length()){
                while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                    i++;
                if (i < line.length() && (line[i] == '(' || line[i] == ')' || line[i] == '*' || line[i] == '+' ||
                                          line[i] == '|')) {
                    expression = string(expression + line[i]);
                    i++;
                }else{

                }
            }
        }*/


        // now we loop back and get the next line in 'Line'
    }

}








std::vector<char> Regex::get_language() {

}
