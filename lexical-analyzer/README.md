# Lexical Analyzer Generator

- This is CC473 first course project, phase 1 of a compiler.

### Phase 1 (Lexical Analyzer Generator):
  - This phase of the project aims to build automatic lexical analyzer generator tools.
  - This tool has two input files, one for grammar rules and the other for source code input.
  - The output of this tool is a list of tokens which matches the user's input file.

### Build and Run
- clone this repo

    `git clone https://github.com/siamx/Lexical_Analyzer`

- build

    `make`

- run using relative path files (files found in this repo `grammar.txt` & `source.txt`)

    `./lexical_analyzer`

- run using custom files, you will be prompted to enter each file path

    `./lexical_analyzer -c`

- tokens are written at the end of `log.txt` file
