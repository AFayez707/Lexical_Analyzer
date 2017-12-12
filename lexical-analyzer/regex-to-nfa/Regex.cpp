//
// Created by abdelrahman on 13/11/17.
//

#include "Regex.h"
#include <fstream>
#include <stack>
#include <iostream>

Regex::Regex(string file_path, ofstream *log_file) {
    this->path = move(file_path);
    this->log_file = log_file;
}

void Regex::parse() {
    vector<string> ids;
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
                    exp_map.insert({keyword, keyword});
                    ids.push_back(keyword);
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
            ids.emplace_back("punctuation");
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
                        char end = line[i];
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
                        char end = line[i];
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

                def_map.insert({exp_name, expression});
                exp_name.clear();
                expression.clear();
            }

            if (i < line.length() && line[i] == ':') {
                ids.push_back(exp_name);
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
                        if (def_map.find(temp) != def_map.end()) {
                            string value = def_map[temp];
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
                exp_map.insert({exp_name, expression});
                exp_name.clear();
                expression.clear();
            }
        }
        // now we loop back and get the next line in 'Line'
    }
    // Close file input stream
    infile.close();

    for (auto it = exp_map.begin(); it != exp_map.end(); ++it) {
        string exp = it->second;

        int i = 0, j, len = exp.length();
        while (i < len) {
            while (((exp[i] == '|' || exp[i] == '(' || exp[i] == ')' || exp[i] == '*' || exp[i] == '+' || exp[i] == 92)
                    && exp[i - 1] != 92) || (exp[i] == 'L' && exp[i - 1] == 92))
                i++;
            if (i >= len)
                break;
            language_characters.insert(exp[i]);
            i++;
        }
    }

    ///// Insert Concatenation
    exp_map = InsertConcatenate(exp_map);

    ///// In-To-Post
    exp_map = InToPost(exp_map);

    for (string id : ids) {
        expressions.emplace_back(id, exp_map[id]);
    }

    *log_file << "Definitions:" << endl;
    for (auto &it : def_map)
        *log_file << "  " << it.first << ": " << it.second << endl;

    *log_file << endl << endl << "Expressions:" << endl;
    for (auto &it : exp_map)
        *log_file << "  " << it.first << ": " << it.second << endl;

    *log_file << endl << endl << "Language:" << endl << "  ";
    for (char c : language_characters)
        *log_file << c << " ";

    *log_file << endl << endl << "Expressions Vector:" << endl;
    for (pair<string, string> c : expressions)
        *log_file << "  " << c.first << ": " << c.second << endl;

    *log_file << endl;
}


map<string, string> Regex::InToPost(map<string, string> exp) {
    for (auto it = exp.begin(); it != exp.end(); ++it) {
        string post;
        string expr = it->second;
        int i = 0, j = 0;
        char ch, cl;
        stack<char> stack1;
        stack1.push('#');
        ch = expr[i];
        while (ch != '\0') {
            if (ch == '(' && expr[i - 1] != 92) {
                stack1.push(ch);
                ch = expr[++i];
            } else if (ch == ')' && expr[i - 1] != 92) {
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
        it->second = post;
    }
    return exp;
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

map<string, string> Regex::InsertConcatenate(map<string, string> exp) {
    for (auto it = exp.begin(); it != exp.end(); ++it) {
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
    return exp;
}