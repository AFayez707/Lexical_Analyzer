//
// Created by ahmed on 12/5/17.
//

#ifndef PARSER_GENERATOR_INPUT_READER_H
#define PARSER_GENERATOR_INPUT_READER_H

#include <set>
#include <map>
#include <vector>

using namespace std;

typedef struct Entry {
    bool is_terminal;
    vector<Entry> production;
} Entry;

class Input_Reader {
public:
    explicit Input_Reader(string file_path);

    set<string> get_terminals();

    map<string, vector<Entry> > get_grammar();

private:
    string file_path;
    set<string> terminals;
    map<string, vector<Entry> > grammar;

    void read_file(string file_path);
};

#endif //PARSER_GENERATOR_INPUT_READER_H
