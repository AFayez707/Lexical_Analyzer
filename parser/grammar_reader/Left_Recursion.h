//
// Created by ahmed on 12/11/17.
//

#ifndef PARSER_GENERATOR_LEFT_RECURSION_H
#define PARSER_GENERATOR_LEFT_RECURSION_H


#include <map>
#include <vector>
#include <fstream>
#include <set>

#define FIRST_FOLLOW    map<string, set<string> >
#define GRAMMAR         map<string, vector<vector<string> > >
#define EPS             "\\EPSILON\\"

using namespace std;

class Left_Recursion {
public:
    Left_Recursion(GRAMMAR grammar, map<string, int> order, set<string> terminals, vector<string> ordered_grammar);

    GRAMMAR get();

    void log(ofstream *log_file);

private:
    GRAMMAR grammar;
    GRAMMAR ambiguity_free_grammar;
    map<string, int> order;
    set<string> terminals;
    vector<string> ordered_grammar;

    /**
     * @brief Responsible for eliminating grammar ambiguity
     */
    void __eliminate();
};


#endif //PARSER_GENERATOR_LEFT_RECURSION_H
