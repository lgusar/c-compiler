#include <stdlib.h>

#include "../src/parser.h"
#include "../src/token.h"
#include "../unity/src/unity.h"

void setUp() {}

void tearDown() {}

struct node *create_node(enum token_type type, char *token_value) {
    struct node *node = malloc(sizeof(struct node));
    struct token *token = malloc(sizeof(struct token));
    ;
    token->token_type = type;
    token->value = token_value;

    node->val = token;
    node->next = NULL;

    return node;
}

void test_parser() {
    struct linked_list tokens;
    tokens.head = create_node(keyword, "int");
    struct node *p = tokens.head;

    p->next = create_node(identifier, "main");
    p = p->next;

    p->next = create_node(open_parenthesis, "(");
    p = p->next;

    p->next = create_node(keyword, "void");
    p = p->next;

    p->next = create_node(close_parenthesis, ")");
    p = p->next;

    p->next = create_node(open_brace, "{");
    p = p->next;

    p->next = create_node(keyword, "return");
    p = p->next;

    p->next = create_node(constant, "2");
    p = p->next;

    p->next = create_node(semicolon, ";");
    p = p->next;

    p->next = create_node(close_brace, "}");
    p = p->next;

    int status = parse(&tokens);
    TEST_ASSERT_EQUAL(0, status);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_parser);
    return UNITY_END();
}
