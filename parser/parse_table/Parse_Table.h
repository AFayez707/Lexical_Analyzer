//
// Created by ahmed on 12/5/17.
//

#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H


#include <map>
#include <set>
#include <vector>
#include <fstream>

#define SYNC        "\\SYNC\\"
#define ERROR       "\\ERROR\\"
#define EPS         "\\EPSILON\\"
#define DOLLAR_SIGN "\\$\\"

#define FIRST_FOLLOW    map<string, set<string> >
#define GRAMMAR         map<string, vector<vector<string> > >
#define TABLE           map<string, map<string, vector<string> > >

using namespace std;

class Parse_Table {
public:
    Parse_Table(FIRST_FOLLOW first, FIRST_FOLLOW follow, GRAMMAR grammar, set<string> terminals);

    vector<string> peek(const string &non_terminal, const string &token);

    void log(ofstream *log_file);

private:
    FIRST_FOLLOW first;
    FIRST_FOLLOW follow;
    GRAMMAR grammar;
    set<string> terminals;
    TABLE parse_table;

    void __sync_and_error();

    void __build_parse_table();
};


#endif //PARSE_TABLE_H
