//
// Created by ahmed on 12/5/17.
//

#ifndef PARSER_GENERATOR_TABLE_GENERATOR_H
#define PARSER_GENERATOR_TABLE_GENERATOR_H

#include <map>
#include <set>

#define mss map<string, set<string> >

using namespace std;

class Table_Generator {
public:
    Table_Generator(mss first, mss follow);

private:
    mss first;
    mss follow;
};


#endif //PARSER_GENERATOR_TABLE_GENERATOR_H
