#include <stdio.h>

#include "file_io.h"
#include "parse_args.h"

#include "lexer.h"
#include "parser.h"

#include "token.h"

int main(int argc, char **argv) {
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret;

    ret = parse_args(argc, argv, &filename, flags);
    if (ret != 0) {
        fprintf(stderr, "parse_args failed\n");
        return 1;
    }

    char *file;
    ret = read_from_file(filename, &file);
    if (ret != 0) {
        fprintf(stderr, "read_from_file_failed\n");
        return 1;
    }

    /* preprocess */

    /* lex */
    struct linked_list *tokens = lex(file);
    if (tokens == NULL) {
        fprintf(stderr, "lex failed\n");
        return 1;
    }

    struct node *p = tokens->head;
    while (p != NULL) {
        printf("%s\n", ((struct token *)(p->val))->value);
        p = p->next;
    }

    if (to_lex) {
        return 0;
    }

    /* parse */
    parse(tokens);
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
