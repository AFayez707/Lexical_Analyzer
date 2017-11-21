//
// Created by abdelrahman on 13/11/17.
//

#include "Regex.h"
#include <fstream>
#include <stack>
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

Regex::Regex(string file_path) {
    this->path = std::move(file_path);
}

vector<pair<string, string> > Regex::parse() {
    map<string, string> exp_map;  //Expressions Map >> Returned
    map<string, string> def_map;  //Definitions Map >> Only Used Here to replace definitions
    ifstream infile(this->path);
    string line, exp_name, expression, temp, keyword, punctuation;
    char low_letter = 'a', up_Letter = 'A', num = '0';

    while (getline(infile, line)) {
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
                if (exp_map.find(keyword) == exp_map.end()) {
                    exp_map[keyword] = keyword;
                    this->expression_names.push_back(keyword);
                }
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
            exp_map.insert({"punctuation", punctuation});
            this->expression_names.push_back("punctuation");
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
                    } else {     // word is already in the def_map
                        while (i < line.length() && isalpha(line[i])) {
                            temp = string(temp + line[i]);
                            i++;
                        }
                        if (def_map.find(temp) != def_map.end()) {
                            string value = def_map[temp];
                            expression = string(expression + value);
                        }
                    }
                    temp.clear();
                }
                if (expression[0] == '(' && expression[expression.length() - 1] == ')' &&
                    expression.find(")|(") != string::npos) {
                    expression.push_back(')');
                    expression.insert(0, 1, '(');
                }

                def_map[exp_name] = expression;
                exp_name.clear();
                expression.clear();
            }

            if (i < line.length() && line[i] == ':') {
                this->expression_names.push_back(exp_name);
                i++;
                while (i < line.length()) {
                    while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                        i++;
                    if (i < line.length() && (line[i] == '(' || line[i] == ')' || line[i] == '*' || line[i] == '+' ||
                                              line[i] == '|')) {
                        expression = line[i];
                        i++;
                    } else if (i < line.length() && isalpha(line[i])) {
                        while (i < line.length() && isalpha(line[i])) {
                            temp = line[i];
                            i++;
                        }
                        if (def_map.find(temp) != def_map.end()) {
                            string value = def_map[temp];
                            expression = string(expression + value);
                        } else {
                            expression = string(expression + temp);
                        }
                    } else {
                        if (line[i] == '.')
                            expression = string(expression + "\\");
                        expression = line[i];
                        i++;
                    }
                    temp.clear();
                }
                exp_map[exp_name] = expression;
                exp_name.clear();
                expression.clear();
            }

        }
        // now we loop back and get the next line in 'Line'
    }

    std::cout << "Definitions:";
    std::cout << std::endl;
    for (auto it = def_map.begin(); it != def_map.end(); ++it) {
        std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Expressions:";
    std::cout << std::endl;
    for (auto it = exp_map.begin(); it != exp_map.end(); ++it) {
        std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Language:";
    std::cout << std::endl;
    for (char c : language_characters) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;


    for (auto it = exp_map.begin(); it != exp_map.end(); ++it) {
        string exp = it->second;

        int i = 0;
        while (i < exp.length()) {
            while (((exp[i] == '|' || exp[i] == '(' || exp[i] == ')' || exp[i] == '*' || exp[i] == '+' || exp[i] == 92)
                    && exp[i - 1] != 92) || (!isprint(exp[i])))
                i++;
            this->language_characters.insert(exp[i]);
            i++;
        }
    }
    this->insert_concatenation(exp_map);
    this->reg_exp_to_post(exp_map);

    for (string name : this->expression_names) {
        this->expressions.push_back(make_pair(name, exp_map[name]));
    }

    return this->expressions;
}

void Regex::insert_concatenation(map<string, string> exp_map) {
    for (auto &it : exp_map) {
        string exp = it.second;

        int i = 0, j, len = (int) (exp.length());
        while (exp[i + 1] != '\0') {
            if ((((exp[i] != '(' && exp[i] != '|' && exp[i] != '\\')
                  || exp[i] == ')'
                  || exp[i] == '*'
                  || exp[i] == '+')
                 &&
                 (exp[i + 1] != ')' && exp[i + 1] != '.' && exp[i + 1] != '|' && exp[i + 1] != '*' &&
                  exp[i + 1] != '+'))) {
                exp += ' ';
                for (j = len + 1; j > i + 1; j--) {
                    exp[j] = exp[j - 1];
                }
                exp[i + 1] = '.';
                len++;
                exp[len] = '\0';
                i++;
            }
            i++;
        }
        it.second = exp;
    }
}

void Regex::reg_exp_to_post(map<string, string> exp_map) {
    for (auto &it : exp_map) {
        string post;
        string expr = it.second;
        int i = 0;
        char ch, cl;
        stack<char> my_stack;
        my_stack.push('#');
        ch = expr[i];
        while (ch != '\0') {
            if (ch == '(') {
                my_stack.push(ch);
                ch = expr[++i];
            } else if (ch == ')') {
                while (my_stack.top() != '(') {
                    post += my_stack.top();
                    my_stack.pop();
                }
                my_stack.pop();
                ch = expr[++i];
            } else if ((ch == '|') || (ch == '.' && expr[i - 1] != 92)) {
                cl = my_stack.top();
                while (Precedence(cl) >= Precedence(ch)) {
                    post += cl;
                    my_stack.pop();
                    cl = my_stack.top();
                }
                my_stack.push(ch);
                ch = expr[++i];
            } else {
                post += ch;
                ch = expr[++i];
            }
        }
        ch = my_stack.top();
        my_stack.pop();
        while ((ch == '|') || (ch == '*') || (ch == '.') || (ch == '+')) {
            post += ch;
            ch = my_stack.top();
            my_stack.pop();
        }
        if (it.first == "punctuation")
            post = expr;
        it.second = post;
    }
}

void Regex::parse2() {
    vector<string> ids;     ///////////////////////Here
    unordered_map<std::string, std::string> ExpMap;  //Expressions Map >> Returned
    unordered_map<std::string, std::string> DefMap;  //Definitions Map >> Only Used Here to replace definitions
    ifstream infile(this->path);
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
                if (ExpMap.find(keyword) == ExpMap.end()) {
                    ExpMap.insert({keyword, keyword});
                    ids.push_back(keyword);    ///////////////////////////// Here
                }
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
            ids.push_back("punctuation");    ///////////////////////////// Here
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

                    if (i < line.length() && (isalpha(line[i]) && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        char start = line[i];
                        i++;
                        while (!isalpha(line[i]))
                            i++;
                        char end = line [i];
                        expression = string(expression + '(');
                        int range = (end - start) + 1;
                        for (int j = 0; j < range; j++)
                            expression = string(expression + (start++) + '|');
                        expression.pop_back();
                        expression = string(expression + ')');
                        i++;
                    } else if (i < line.length() && (isdigit(line[i]) && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        char start = line[i];
                        i++;
                        while (!isdigit(line[i]))
                            i++;
                        char end = line [i];
                        expression = string(expression + '(');
                        int range = (end - start) + 1;
                        for (int j = 0; j < range; j++)
                            expression = string(expression + (start++) + '|');
                        expression.pop_back();
                        expression = string(expression + ')');
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
                if (expression[0] == '(' && expression[expression.length() - 1] == ')' &&
                    expression.find(")|(") != std::string::npos) {
                    expression.push_back(')');
                    expression.insert(0, 1, '(');
                }

                DefMap.insert({exp_name, expression});
                exp_name.clear();
                expression.clear();
            }

            if (i < line.length() && line[i] == ':') {
                ids.push_back(exp_name);    ///////////////////////////// Here
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


    for (auto it = ExpMap.begin(); it != ExpMap.end(); ++it) {
        string exp = it->second;

        int i = 0, j, len = exp.length();
        while (i < len) {
            while (((exp[i] == '|' || exp[i] == '(' || exp[i] == ')' || exp[i] == '*' || exp[i] == '+' || exp[i] == 92)
                    && exp[i - 1] != 92) || (exp[i] == 'L' && exp[i - 1] == 92))
                i++;
            if(!(i<len))
                break;
            language_characters.insert(exp[i]);
            i++;
        }
    }

    ///// Insert Concatenation
    for (auto it = ExpMap.begin(); it != ExpMap.end(); ++it) {
        string exp = it->second;

        int i = 0, j, len = exp.length();
        while (exp[i + 1] != '\0') {
            if ((((exp[i] != '(' /*&& exp[i] != '.'*/ && exp[i] != '|' && exp[i] != '\\')
                  || exp[i] == ')'
                  || exp[i] == '*'
                  || exp[i] == '+')
                 &&
                 (exp[i + 1] != ')' && exp[i + 1] != '.' && exp[i + 1] != '|' && exp[i + 1] != '*' &&
                  exp[i + 1] != '+'))) {
                exp = string(exp + ' ');
                for (j = len + 1; j > i + 1; j--) {
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

    ///// In-To-Post
    for (auto it = ExpMap.begin(); it != ExpMap.end(); ++it) {
        string post;
        string expr = it->second;
        int i = 0, j = 0;
        char ch, cl;
        stack<char> stack1;
        stack1.push('#');
        ch = expr[i];
        while (ch != '\0') {
            if (ch == '(' && expr[i-1] != 92) {
                stack1.push(ch);
                ch = expr[++i];
            } else if (ch == ')' && expr[i-1] != 92) {
                while (stack1.top() != '(') {
                    post = string(post + stack1.top());
                    stack1.pop();
                }
                stack1.pop();
                ch = expr[++i];
            } else if ((ch == '|') || (ch == '.' && expr[i - 1] != 92)) {
                cl = stack1.top();
                while (Precedence(cl) >= Precedence(ch)) {
                    post = string(post + cl);
                    stack1.pop();
                    cl = stack1.top();
                }
                stack1.push(ch);
                ch = expr[++i];
            } else {
                post = string(post + ch);
                ch = expr[++i];
            }
        }
        ch = stack1.top();
        stack1.pop();
        while ((ch == '|') || (ch == '*') || (ch == '.') || (ch == '+')) {
            post = string(post + ch);
            ch = stack1.top();
            stack1.pop();
        }
//        if (it->first == "punctuation")
//            post = expr;
        it->second = post;

    }


    for (string id : ids) {
        expressions.push_back(make_pair(id,ExpMap[id]));
    }


    std::cout << "Definitions:";
    std::cout << std::endl;
    for (auto it = DefMap.begin(); it != DefMap.end(); ++it) {
        std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Expressions:";
    std::cout << std::endl;
    for (auto it = ExpMap.begin(); it != ExpMap.end(); ++it) {
        std::cout << " " << it->first << ":" << it->second;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Language:";
    std::cout << std::endl;
    for (char c : language_characters) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "ids Vector:";
    std::cout << std::endl;
    for (pair<string, string> c : expressions) {
        std::cout << c.first << ":" << c.second << endl;
    }
}


int Regex::Precedence(char symbol) {
    int priority;
    switch (symbol) {
        case '|':
            priority = 1;
            break;
        case '.':
            priority = 2;
            break;
        case '*':
            priority = 3;
            break;
        case '+':
            priority = 4;
            break;
        default:
            priority = 0;
            break;
    }
    return priority;
}

set<char> Regex::get_language() {
    return language_characters;
}
