//
// Created by abdelrahman on 13/11/17.
//

#include "Regex.h"
#include <fstream>
#include <stack>

Regex::Regex(string file_path) {
    this->path = std::move(file_path);
}

map<string, string> Regex::parse() {
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
                    keyword += line[i];
                    i++;
                }
                if (exp_map.find(keyword) == exp_map.end())
                    exp_map[keyword] = keyword;
                keyword.clear();
            }
        } else if (i < line.length() && line[i] == '[') {
            i++;
            while (i < line.length() && line[i] != ']') {
                while (i < line.length() && (line[i] == ' ' || line[i] == '\t'))
                    i++;
                punctuation += line[i];
                if (line[i] != 92)
                    punctuation += '|';
                i++;
            }
            punctuation.pop_back();
            exp_map.insert({"punctuation", punctuation});
            punctuation.clear();
        } else {
            while (i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] != '=' && line[i] != ':')
                exp_name += line[i++];

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
                        expression += '(';
                        for (int j = 0; j < 26; j++)
                            expression += ((low_letter++) + '|');
                        expression.pop_back();
                        expression += ')';
                        while (line[i] != 'z')
                            i++;
                        i++;
                    } else if (i < line.length() && (line[i] == 'A' && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        expression += '(';
                        for (int j = 0; j < 26; j++)
                            expression += ((up_Letter++) + '|');
                        expression.pop_back();
                        expression += ')';
                        while (line[i] != 'Z')
                            i++;
                        i++;
                    } else if (i < line.length() && (line[i] == '0' && (line[i + 1] == '-' || line[i + 2] == '-'))) {
                        expression += '(';
                        for (int j = 0; j < 10; j++)
                            expression += ((num++) + '|');
                        expression.pop_back();
                        expression += ')';
                        while (line[i] != '9')
                            i++;
                        i++;
                    } else if (i < line.length() &&
                               (line[i] == '(' || line[i] == ')' || line[i] == '*' || line[i] == '+' ||
                                line[i] == '|')) {
                        expression += line[i];
                        i++;
                    } else {     // word is already in the def_map
                        while (i < line.length() && isalpha(line[i])) {
                            temp += line[i];
                            i++;
                        }
                        if (def_map.find(temp) != def_map.end()) {
                            string value = def_map[temp];
                            expression += value;
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
                            expression += value;
                        } else {
                            expression += temp;
                        }
                    } else {
                        if (line[i] == '.')
                            expression += '\\';
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
    this->insert_concatenation(exp_map);
    this->reg_exp_to_post(exp_map);
    return exp_map;
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
                while (precedence(cl) >= precedence(ch)) {
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


int Regex::precedence(char symbol) {
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

}
