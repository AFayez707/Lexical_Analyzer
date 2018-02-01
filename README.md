# Compiler front end generators.

## (Lexical analyzer generator)[lexical-analyzer]

- Read Grammar file `grammar.txt` line by line, then substitute ranges.

    `digit = 0 - 9` => `digit = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9`

- Convert each range from infix to postfix.

    `digit = 0 | 1 | 2 | 3` => `digit = 0 1 | 2 | 3 |`

- Convert each postfix to an equivalent NFA using `Thompson's construction algorithm`.
- Convert the generated NFA to DFA using `Subset construction algorithm`.
- Minimize the generated DFA using `Hopcroft's algorithm`.
- Read & tokenize `source.txt` file.

## (Parser generator)[parser]

- Read `java_cfg.txt`
- Remove Left recursion if found.
- Perform Left factoring, only one is supported.

    `A -> B D | B F`      => Supported

    `A -> B | B D | B F`  => NOT supported

- Calculate First & Follow for each non terminal.
- Build the parse table with panic mode error recovery support.
- Parse tokens read from `stdin`.

## Build and Run

- clone this repo

    `git clone https://github.com/siamx/compiler-front-end`

- Enter project directory

    `cd compiler-front-end`

- Build

    `make`

- Run

    `./lex | ./parse`
