//
// Created by ahmed on 12/11/17.
//
#include "parser/Parser.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    queue<string> tokens;

    ifstream in("tokens.txt");
    string token;
    while (getline(in, token)) tokens.push(token);
    tokens.push(DOLLAR_SIGN);

//    if (argc == 1) {
//        string line;
//        while (getline(cin, line)) {
//            string token = line.substr(0, line.find_first_of(' '));
//            if (token == "lexical_error:") {
//                cout << "Warning, lex reported an error => " << line.c_str() << endl;
//            } else {
//                tokens.push(token);
//                cout << "" << token << endl;
//            }
//        }
//    } else if (argc == 3) {
//        // TODO: to be written
//    } else {
//        cout << "Invalid number of params, parse takes zero or two params.\n\n"
//                "pipe lex out put using -> ./lex | ./parse\n\n"
//                "            two params -> ./parse [java_cfg.txt file path] [tokens file path]\n\n";
//        exit(1);
//    }

    Parser parser("java_cfg.txt", "parser-log.txt", tokens);
    parser.parse();

    return EXIT_SUCCESS;
}
