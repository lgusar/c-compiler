#include "parse_args.h"

int main(int argc, char **argv) {
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    parse_args(argc, argv, &filename, flags);

    /* preprocess */

    /* lex */
    if (to_lex) {
        return 0;
    }
    /* parse */
    if (to_parse) {
        return 0;
    }

    /* assemble */
    if (to_codegen) {
        return 0;
    }

    /* emit code */
    return 0;
}
