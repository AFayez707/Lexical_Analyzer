# Design Document

## how to write a design document
first before you start contributing to to this design document, read about design documents on the internet. This 
[link](http://www.eecs.harvard.edu/~cs161/resources/design.pdf) is good introduction to what that the design document
will look like.

## Outline
This design document will also serve as the project report and will include the details of the project modules,
their API, how do they fit together, data structures and algorithms used.

The following is an outline of some of the modules:
- Converting all regular definitions and regular expressions to a set of regular expressions that uses only the
operators alternation `|`, concatenation, kleene closure, and parenthesis.
- Converting the regular expressions from the previous step from infix to postfix notation.
- Converting postfix regular expressions to NFAs using Thompson Construction.
- Converting NFAs to DFAs using subset construction.
- Minimizing the generated DFA and obtaining its transition table.
- Generating the lexical analyzer which simulates the transition table.
- Data Stuctures and Algorithms Used

### Converting Regular Expressions to NFAs
The inputs to this module is a regular expression that contains only letters of the input language and the 
symbols `(, ), |, *, .` only. Note that the dot (`.`) is the concatenation operator and it is not included in the
original RE, but it is generated when the RE is converted from infix to postfix notation The regular expression in 
converting from infix notation to postfix notation while maintaining a stack of NFAs that correspond to the evaluated
sub expressions. The algorithm reads in a character from the RE and depending on its type (operator or
language character) either pops items from the stack and applies the operation to them or pushes an NFA that accepts
the single character if it's a language character. When the algorithm finishes consuming characters of the RE, only one
item will be on the stack and this item is the NFA that accepts this RE, which is the desired output. If after 
finishing the RE, there are more than one item on the stack then the input RE was invalid.

The step of taking to separate NFAs and either concatenating them or alternating them may not seem apparent at the 
beginning. But since each NFA knows its start and end states, you can easily combine them as Thompson Construction 
outlines. For example, let S1, E1, S2, E2 be start and end nodes of two NFAs we want to combine using alternation.
To make the resulting NFA we create a new start state that has epsilon transitions to S1 and S2 and create a new end 
state that E1 and E2 are connected to with epsilon transitions.

### Representing an NFA

An NFA has a set of states, a start state, and an end state. States have a hash map of characters to states that denote
the transitions on each input symbol, and a list of transitions on epsilon (because there can be multiple transition
on epsilon).

NFAs support the following operations:
- `concatenate(NFA n)`: concatenates `this` NFA with `n` by creating an NFA that accepts the concatenation set of 
strings accepted by `this` and the set of strings accepted by `n`.
- `alternate(NFA n)`: alternates `this` NFA with `n` by creating an NFA that accepts the set of strings accepted 
by `this` or the set of strings accepted by `n`.
- `iterate`: creates an NFA that accepts the strings accepted by `this` concatenated with itself 0 or more times.
- `closure(State s)`: returns the set of states that are the epsilon closure of s.
- `move(State s, Char c)`: returns the state that is reachable from s on one transition on c. or null if such
transition doesn't exist.
- `finalize`: sets the current end state as an accepting state.

Some undetermined design decisions:
- `closure()` and `move()` could return a state ID instead of the state itself to avoid exposing how the states are 
represented and allow for the representation to change.
- `conacenate()`, `alternate()`, `iterate()` could either modify `this` NFA or return a new one.

### A global ID generator
To simplify state generation and modification of NFAs, we can use a global ID generator for state IDs that generate a 
unique number each time it is called.

### Representing a DFA
a DFA is generated from a corresponding NFA using the subset construction algorithm. Each DFA state needs to keep track
of the set of NFA states it correspond to. Unlike an NFA, a DFA is backed-up (represented) by its transition table,
which can roughly be thought of as an adjacency matrix.

### NFA to DFA using Subset Construction
The subset construction algorithm needs to perform the operations `closure(Set<State>)` and `move(Set<State>, char)` 
which are already implemented by the NFA. It will also need to know the start symbol and whether a particular state is
an accepting state or not.

Design Decisions:
- we can memoize the epsilon closure of each NFA state to avoid recomputing it each time. We will still need to combine
the epsilon closure of several states. This is an example or space vs time complexity trade-off.