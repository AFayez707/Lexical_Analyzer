//
// Created by ahmed on 12/11/17.
//

#ifndef PARSER_GENERATOR_FIRST_H
#define PARSER_GENERATOR_FIRST_H


#include <map>
#include <set>
#include <vector>

#define FIRST_FOLLOW    map<string, set<string> >
#define GRAMMAR         map<string, vector<vector<string> > >

using namespace std;

class First {
public:
    explicit First(string start_symbol, GRAMMAR grammar);

    FIRST_FOLLOW get();

    void log(ofstream *log_file);

private:
    string start_symbol;
    FIRST_FOLLOW first;
    GRAMMAR grammar;

    /**
     * @brief Responsible for generating each non-terminal's first terminals
     */
    void __generate();
};


#endif //PARSER_GENERATOR_FIRST_H
