#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "parser.h"
#include "token.h"

int program(struct node *token_node, int depth);
int function(struct node *token_node, int depth);
int statement(struct node *token_node, int depth);
int expression(struct node *token_node, int depth);
int ident(struct node *token_node, int depth);
int integer(struct node *token_node, int depth);

int expect(struct node *token_node, enum token_type expected_type);

void depth_printf(char *text, int depth);

void error_log(char **expected_values, int n);

int parse(struct linked_list *input_tokens) {
    return program(input_tokens->head, 0);
}

int program(struct node *token_node, int depth) {
    depth_printf("Program(\n", depth);

    function(token_node, depth + 1);

    return 0;
}

int function(struct node *token_node, int depth) {
    depth_printf("Function(\n", depth);

    expect(token_node, keyword);
    ident(token_node, depth + 1);
    expect(token_node, open_parenthesis);
    expect(token_node, keyword);
    expect(token_node, close_parenthesis);
    expect(token_node, open_brace);
    statement(token_node, depth + 1);
    expect(token_node, close_brace);

    return 0;
}

int ident(struct node *token_node, int depth) {
    depth_printf("Identifier(\n", depth);

    expect(token_node, identifier);
    return 0;
}

int statement(struct node *token_node, int depth) {
    depth_printf("Statement(\n", depth);

    expect(token_node, keyword);
    expression(token_node, depth + 1);

    return 0;
}

int expression(struct node *token_node, int depth) {
    depth_printf("Expression(\n", depth);

    integer(token_node, depth + 1);

    return 0;
}

int integer(struct node *token_node, int depth) {
    depth_printf("Int(\n", depth);

    expect(token_node, constant);

    return 1;
}

int expect(struct node *token_node, enum token_type expected_type) {
    struct token *token = (struct token *)token_node->val;
    if (token->token_type != expected_type) {
        fprintf(stderr, "parser: expected %s\n", get_token_type(expected_type));
        exit(1);
    }
    token_node = token_node->next;
    return 0;
}

void depth_printf(char *text, int depth) { printf("%*s", depth, text); }
