# Lexical Analyzer Generator

- This is CC473 first course project, phase 1 of a compiler front end.

### Phase 1 (Lexical Analyzer Generator):
- This phase of the project aims to build automatic lexical analyzer generator tools.
- This tool has two input files, one for grammar rules and the other for source code input.
- The output of this tool is a list of tokens which matches the user's input file.

### Build and Run
- clone this repo

    `git clone https://github.com/siamx/compiler-front-end`

- Enter project directory

    `cd compiler-front-end/lexical-analyzer`

- Build

    `make`

- Run using relative path files (files found in this repo `grammar.txt` & `source.txt`)

    `./lex`

- Run using custom files, enter each file path

    `./lex  [grammar file path]  [source file path]`

- Check `lex-log.txt` for NFA, DFA & Expression caculations in detail

### Further details & `grammar.txt` file format [here](Lexical_Analyzer_Generator.pdf)
