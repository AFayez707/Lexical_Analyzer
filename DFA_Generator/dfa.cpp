//
// Created by ahmed on 14/11/17.
//

#include "dfa.h"

struct transition {
    int from;
    int to;
    char value;
};

class dfa {
public:

    vector<transitions>     transitions;
    vector<vector<int>>     entries;
    vector<bool>            isMarked;
    vector<int>             finalStates;

    /* Add new DFA Entry */
    int AddEntry(vector<int> entry) {
        entries.push_back(entry);
        isMarked.push_back(false);
        return entries.size() - 1;
    }

    /* Return the next unMarked entry */
    int GetNextUnMarkedIndex() {
        for (int index=0; i < isMarked.size(); index++) {
            if (!isMarked.at(index)) {
                return index;
            }
        }
        /* All is marked */
        return -1;
    }

    /* Mark entry with given index */
    void MarkEntry(int index) {
        isMarked.at(index) = true;
    }

    /* Get Entry using it's index */
    vector<int> GetEntry(int index) {
        return entries.at(index);
    }

    /* Search for entry */
    int FindEntry(vector<int> entry) {
        for (int i = 0; i < entries.size(); i++) {
            vector<int> it = entries.at(i);
            if (it == entry) {
                return i;
            }
        }
        /* Not Found */
        return -1;
    }

    void SetFinalState(int nfa_fs) {
        for (int i = 0; i < entries.size(); i++) {
            vector<int> entry = entries.at(i);

            for (int j = 0; j < entry.size(); j++) {
                int vertex = entry.at(j);
                if (vertex == nfa_fs) {
                    finalStates.push_back(i);
                }
            }
        }

    }

    string GetFinalState() {
        return join(finalStates, ",");
    }

    /* Set new transition values */
    void SetTransition(int from, int to, char value) {
        transition trans;
        trans.from = from;
        trans.to = to;
        trans.value = value;
        transitions.push_back(trans);
    }

    void display() {
        transition newTransition;
        cout<<"\n";
        for(int i = 0; i < transitions.size(); i++) {
            newTransition = transitions.at(i);
            cout <<"q" << newTransition.from << " {" << join(entries.at(newTransition.from), ",")
                 <<"} -> q" << newTransition.to<<" {" << join(entries.at(newTransition.to), ",")
                 <<"} : Symbol - " << newTransition.value<<endl;
        }
        cout<<"\nThe final state is q : "<< join(finalStates, ",") << endl;
    }

};