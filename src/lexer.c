#include <stdio.h>

#include "lexer.h"
#include "linked_list.h"
#include "token.h"

int lex(char *file, struct linked_list tokens) {
    int ret = get_tokens(file, &tokens);
    if (ret != 0) {
        fprintf(stderr, "get_tokens failed\n");
    }
    return ret;
}
