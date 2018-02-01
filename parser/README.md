# Parser Generator

- This is CC473 first course project, phase 2 of a compiler front end.

### Phase 2 (Parser Generator):
- This phase of the project aims to build automatic parser generator tools.
- This tool has 1 input file `java_cfg.txt` & stdin tokens (Lexical analyzer output).
- The output is the predictive parsing table of the generated parser as well as the leftmost derivation sententials one per line.

### Build and Run

- clone this repo

    `git clone https://github.com/siamx/compiler-front-end`

- Enter project directory

    `cd compiler-front-end/parser`

- Build

    `make`

- Run

    - Make sure you have `java_cfg.txt` file in the same directory with the binary

    - Run by piping lexical analyzer output

        `./lex | ./parse`

    - Run by entering tokens manually, terminated by an empty line

        `./parse

- Check `parse-log.txt` for NFA, DFA & Expression caculations in detail

### Further details and `java_cfg.txt` file format [here](Parser_Generator.pdf)
