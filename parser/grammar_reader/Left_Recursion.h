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

using namespace std;

class Left_Recursion {
public:
    Left_Recursion(string start_symbol, GRAMMAR grammar);

    GRAMMAR get();

    void log(ofstream *log_file);

private:
    string start_symbol;
    GRAMMAR grammar;
    GRAMMAR non_ambiguous_grammar;

    /**
     * @brief Responsible for eliminating grammar ambiguity
     */
    void __eliminate();
};


#endif //PARSER_GENERATOR_LEFT_RECURSION_H
