//
// Created by ahmed on 12/11/17.
//

#ifndef PARSER_GENERATOR_FOLLOW_H
#define PARSER_GENERATOR_FOLLOW_H


#include <map>
#include <set>
#include <vector>
#include <fstream>

#define FIRST_FOLLOW    map<string, set<string> >
#define GRAMMAR         map<string, vector<vector<string> > >

using namespace std;

class Follow {
public:
    explicit Follow(string start_symbol, GRAMMAR grammar);

    FIRST_FOLLOW get();

    void log(ofstream *log_file);

private:
    string start_symbol;
    FIRST_FOLLOW follow;
    GRAMMAR grammar;

    /**
    * @brief Responsible for generating each non-terminal's follow terminals
    */
    void __generate();
};


#endif //PARSER_GENERATOR_FOLLOW_H
