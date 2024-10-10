#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "linked_list.h"
#include "token.h"

struct linked_list *lex(char *file) {
    struct linked_list *tokens = linked_list_init();

    int ret = get_tokens(file, tokens);
    if (ret != 0) {
        fprintf(stderr, "get_tokens failed\n");
        free(tokens);
        tokens = NULL;
    }

    return tokens;
}
