#ifndef _TOKEN_H
#define _TOKEN_H

#include "linked_list.h"

enum token_type {
    k_int,
    k_return,
    k_void,
    identifier,
    open_parenthesis,
    close_parenthesis,
    open_brace,
    close_brace,
    constant,
    semicolon,
    undefined,
};

struct token {
    enum token_type token_type;
    /* TODO: convert to void * */
    char *value;
};

int get_token(char **string, struct token *result);

int get_tokens(char *string, struct linked_list *result);

char *get_token_type(enum token_type);

#endif /* _TOKEN_H */
