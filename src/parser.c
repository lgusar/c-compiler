#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "parser.h"
#include "token.h"

struct ast_program *parse_program(struct node **token_node, int depth);
struct ast_function_definition *parse_function(struct node **token_node,
                                               int depth);
struct ast_statement *parse_statement(struct node **token_node, int depth);
struct ast_expression *parse_expression(struct node **token_node, int depth);
struct ast_identifier *parse_identifier(struct node **token_node, int depth);
struct ast_int *parse_int(struct node **token_node, int depth);

int expect(struct node **token_node, enum token_type expected_type);

int get_string_value(struct node **token_node, enum token_type expected_type,
                     char **output);

int get_int_value(struct node **token_node, enum token_type expected_type,
                  int *output);

void depth_printf(char *text, int depth);

void error_log(char **expected_values, int n);

struct ast_program *parse(struct linked_list *input_tokens) {
    struct node **p = &input_tokens->head;
    struct ast_program *end_node = parse_program(p, 0);

    if (*p != NULL) {
        fprintf(stderr, "Unexpected token\n");
        exit(1);
    }

    return end_node;
}

struct ast_program *parse_program(struct node **token_node, int depth) {
    struct ast_program *program = malloc(sizeof(struct ast_program));
    depth_printf("Program\n", depth);

    program->function_definition = parse_function(token_node, depth + 1);

    return program;
}

struct ast_function_definition *parse_function(struct node **token_node,
                                               int depth) {
    struct ast_function_definition *function =
        malloc(sizeof(struct ast_function_definition));
    depth_printf("Function\n", depth);

    expect(token_node, k_int);
    function->name = parse_identifier(token_node, depth + 1);
    expect(token_node, open_parenthesis);
    expect(token_node, k_void);
    expect(token_node, close_parenthesis);
    expect(token_node, open_brace);
    function->body = parse_statement(token_node, depth + 1);
    expect(token_node, close_brace);

    return function;
}

struct ast_identifier *parse_identifier(struct node **token_node, int depth) {
    struct ast_identifier *ast_identifier =
        malloc(sizeof(struct ast_identifier));
    ast_identifier->value = malloc(sizeof(char) * MAX_IDENTIFIER_SIZE);
    get_string_value(token_node, identifier, &(ast_identifier->value));

    depth_printf("Identifier(", depth);
    printf("%s)\n", ast_identifier->value);

    return ast_identifier;
}

struct ast_statement *parse_statement(struct node **token_node, int depth) {
    struct ast_statement *ast_statement = malloc(sizeof(struct ast_statement));

    depth_printf("Statement\n", depth);

    expect(token_node, k_return);
    ast_statement->exp = parse_expression(token_node, depth + 1);
    expect(token_node, semicolon);

    return ast_statement;
}

struct ast_expression *parse_expression(struct node **token_node, int depth) {
    struct ast_expression *ast_expression =
        malloc(sizeof(struct ast_expression));

    depth_printf("Expression\n", depth);

    ast_expression->integer = parse_int(token_node, depth + 1);

    return ast_expression;
}

struct ast_int *parse_int(struct node **token_node, int depth) {
    struct ast_int *ast_int = malloc(sizeof(struct ast_int));
    get_int_value(token_node, constant, &ast_int->value);

    depth_printf("Constant(", depth);
    printf("%d)\n", ast_int->value);

    return ast_int;
}

int expect(struct node **token_node, enum token_type expected_type) {
    struct token *token = (struct token *)(*token_node)->val;
    if (token->token_type != expected_type) {
        fprintf(stderr, "parser: expected %s but found %s\n",
                get_token_type(expected_type),
                token->value);
        exit(1);
    }
    *token_node = (*token_node)->next;
    return 0;
}

int get_string_value(struct node **token_node, enum token_type expected_type,
                     char **output) {
    struct token *token = (struct token *)(*token_node)->val;
    if (token->token_type != expected_type) {
        fprintf(stderr, "parser: expected %s but found %s\n",
                get_token_type(expected_type),
                token->value);
        exit(1);
    }
    strcpy(*output, token->value);
    *token_node = (*token_node)->next;
    return 0;
}

int get_int_value(struct node **token_node, enum token_type expected_type,
                  int *output) {
    struct token *token = (struct token *)(*token_node)->val;
    if (token->token_type != expected_type) {
        fprintf(stderr, "parser: expected %s but found %s\n",
                get_token_type(expected_type),
                token->value);
        exit(1);
    }
    *output = atoi(token->value);
    *token_node = (*token_node)->next;
    return 0;
}
void depth_printf(char *text, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s", text);
}
