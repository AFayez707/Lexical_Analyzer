//
// Created by ahmed on 14/11/17.
//

#include "dfa.h"


/* Add new DFA Entry */
int dfa::AddEntry(vector<int> entry) {
    entries.push_back(entry);
    isMarked.push_back(false);
    return entries.size() - 1;
}

/* Return the next unMarked entry */
int dfa::GetNextUnMarkedIndex() {
    for (int index = 0; index < isMarked.size(); index++) {
        if (!isMarked.at(index)) {
            return index;
        }
    }
    /* All is marked */
    return -1;
}

/* Mark entry with given index */
void dfa::MarkEntry(int index) {
    isMarked.at(index) = true;
}

/* Get Entry using it's index */
vector<int> dfa::GetEntry(int index) {
    return entries.at(index);
}

/* Search for entry */
int dfa::FindEntry(vector<int> entry) {
    for (int i = 0; i < entries.size(); i++) {
        vector<int> it = entries.at(i);
        if (it == entry) {
            return i;
        }
    }
    /* Not Found */
    return -1;
}

void dfa::SetFinalState(int nfa_fs) {
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

string dfa::GetFinalState() {
    return join(finalStates, ",");
}

/* Set new transition values */
void dfa::SetTransition(int from, int to, char value) {
    transition trans;
    trans.from = from;
    trans.to = to;
    trans.value = value;
    transitions.push_back(trans);
}

void dfa::display() {
    transition newTransition;
    cout << "\n";
    for (int i = 0; i < transitions.size(); i++) {
        newTransition = transitions.at(i);
        cout << "q" << newTransition.from << " {" << join(entries.at(newTransition.from), ",")
             << "} -> q" << newTransition.to << " {" << join(entries.at(newTransition.to), ",")
             << "} : Symbol - " << newTransition.value << endl;
    }
    cout << "\nThe final state is q : " << join(finalStates, ",") << endl;
}

set<int> dfa::vector_to_set(vector<int> vec) {
    set<int> result;

    for (int element : vec)
        result.insert(element);

    return result;
}

/**
 * Implements the subset construction algorithm as described in the reference
 */
dfa::dfa(nfa *n, set<char> language) {
    // initially e-closure(S0) is the only state in Dstates, and it is unmarked
    set<int> start;
    start.insert(n->get_start_state());
    set<int> s = n->epsilon_closure(start);
    AddEntry(set_to_vector(s));

    // while ( there is an unmarked state T in Dstates )
    int T_index;
    while ((T_index = GetNextUnMarkedIndex()) != -1) {
        // Mark T
        MarkEntry(T_index);
        vector<int> T_vec = GetEntry(T_index);
        set<int> T_set = vector_to_set(T_vec);

        // for each input symbol a
        for (char a : language) {
            // U = e-closure(move(T,a))
            set<int> U_set = n->epsilon_closure(n->move(T_set, a));
            vector<int> U_vec = set_to_vector(U_set);

            // if ( U is not in Dstates )
            int U_index;
            if ((U_index = FindEntry(U_vec)) != -1)
                // add U as an unmarked state to Dstates
                U_index = AddEntry(U_vec);
            SetTransition(T_index, U_index, a);
        }

    }

}

vector<int> dfa::set_to_vector(set<int> set) {
    vector<int> result;

    for (int element : set)
        result.push_back(element);

    return result;
}




