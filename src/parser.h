#ifndef _PARSER_H
#define _PARSER_H

#include "linked_list.h"

#define MAX_IDENTIFIER_SIZE 128
struct ast_identifier {
    char *value;
};

struct ast_int {
    int value;
};

struct ast_expression {
    struct ast_int *integer;
};

struct ast_statement {
    struct ast_expression *exp;
};

struct ast_function_definition {
    struct ast_identifier *name;
    struct ast_statement *body;
};

struct ast_program {
    struct ast_function_definition *function_definition;
};

struct ast_program *parse(struct linked_list *input_tokens);

#endif /* _PARSER_H */
