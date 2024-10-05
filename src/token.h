#ifndef _TOKEN_H
#define _TOKEN_H

#include "linked_list.h"

enum token_type {
    keyword,
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
    char *value;
};

int get_token(char **string, struct token *result);

int get_tokens(char *string, struct linked_list *result);

#endif /* _TOKEN_H */
