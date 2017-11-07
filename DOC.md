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