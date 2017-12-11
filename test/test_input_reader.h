//
// Created by ahmed on 12/9/17.
//

#ifndef PARSER_GENERATOR_TEST_INPUT_READER_H
#define PARSER_GENERATOR_TEST_INPUT_READER_H

#include "../parser-generator/grammar_reader/CFG_Reader.h"

void run_input_reader_test();

void run_input_reader_test() {
    auto *logger = new ofstream("parser-log.txt", ios_base::app);

    CFG_Reader ir("java_cfg.txt");
    ir.log(logger);

    logger->close();
}

#endif //PARSER_GENERATOR_TEST_INPUT_READER_H
