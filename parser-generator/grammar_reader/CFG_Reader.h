//
// Created by ahmed on 12/5/17.
//

#ifndef PARSER_GENERATOR_INPUT_READER_H
#define PARSER_GENERATOR_INPUT_READER_H

#include <set>
#include <map>
#include <vector>

#define MSV map<string, vector<vector<string> > >

using namespace std;

// Context Free Grammar Reader
class CFG_Reader {
public:
    explicit CFG_Reader(string file_path);

    MSV get_grammar();

    set<string> get_terminals();

    string get_start_symbol();

    void display();

private:
    string file_path;
    string start_symbol;
    MSV grammar;
    set<string> terminals;

    void __read(string file_path);
};

#endif //PARSER_GENERATOR_INPUT_READER_H
