//
// Created by ahmed on 12/11/17.
//

#ifndef PARSER_GENERATOR_LEFT_RECURSION_H
#define PARSER_GENERATOR_LEFT_RECURSION_H


#include <map>
#include <vector>
#include <fstream>

#define FIRST_FOLLOW    map<string, set<string> >
#define GRAMMAR         map<string, vector<vector<string> > >
#define EPS             "\\EPSILON\\"

using namespace std;

class Left_Recursion {
public:
    Left_Recursion(string start_symbol, GRAMMAR grammar, map<string, int> order);

    GRAMMAR get();

    void log(ofstream *log_file);

private:
    string start_symbol;
    GRAMMAR grammar;
    GRAMMAR ambiguity_free_grammar;
    map<string, int> order;

    /**
     * @brief Responsible for eliminating grammar ambiguity
     */
    void __eliminate();
};


#endif //PARSER_GENERATOR_LEFT_RECURSION_H
