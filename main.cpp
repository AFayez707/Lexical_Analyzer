//
// Created by ahmed on 12/11/17.
//
#include "parser/Parser.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    queue<string> tokens;

//    ifstream in("tokens.txt");
//    string token;
//    while (getline(in, token)) tokens.push(token);
//    tokens.push(DOLLAR_SIGN);

    if (argc == 1) {
        string line;
        while (getline(cin, line)) {
            string token = line.substr(0, line.find_first_of(' '));
            if (token == "lexical_error:") {
                cout << "Warning => " << line.c_str() << endl;
            } else {
                tokens.push(token);
                cout << line << endl;
            }
        }
    } else {
        cout << "Invalid number of params, parse takes zero or two params.\n\n"
                "pipe lex out put using -> ./lex | ./parse\n\n";
        exit(1);
    }

    tokens.push(DOLLAR_SIGN);

    Parser parser("java_cfg.txt", "parser-log.txt", tokens);
    parser.parse();

    return EXIT_SUCCESS;
}
