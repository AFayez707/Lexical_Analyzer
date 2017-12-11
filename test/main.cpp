#include "test_parse_table.h"
#include "test_input_reader.h"
#include "test_parser.h"

int main() {
    run_input_reader_test();
    Parse_Table *parse_table = run_parse_table_test();
    run_test_parser(parse_table);
}
