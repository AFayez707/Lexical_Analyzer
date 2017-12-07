//
// Created by ahmed on 12/5/17.
//

#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H

#include <map>
#include <set>
#include <vector>

#define ERROR "\\ERROR\\"
#define EPS "\\EPSILON\\"
#define DOLLAR_SIGN "$"
#define MSS map<string, set<string> >
#define MSV map<string, vector<vector<string> > >
#define TABLE map<string, map<string, vector<string> > >

using namespace std;

class Parse_Table {
public:
    Parse_Table(MSS first, MSS follow, MSV grammar, set<string> terminals);

    vector<string> get_transition(string stack_top, string token);

    void display_parse_table();

private:
    MSS first;
    MSS follow;
    MSV grammar;
    set<string> terminals;
    TABLE parse_table;

    void build_parse_table();
};

#endif //PARSE_TABLE_H
