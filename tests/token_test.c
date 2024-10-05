#include <string.h>

#include "../src/token.h"
#include "../unity/src/unity.h"

void setUp() {}

void tearDown() {}

void test_get_token_keyword() {
    char *input = "int";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(keyword, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("int", result.value));
}

void test_get_token_identifier() {
    char *input = "main";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(identifier, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("main", result.value));
}

void test_get_token_open_parenthesis() {
    char *input = "(";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(open_parenthesis, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("(", result.value));
}

void test_get_token_close_parenthesis() {
    char *input = ")";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(close_parenthesis, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp(")", result.value));
}

void test_get_token_open_brace() {
    char *input = "{";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(open_brace, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("{", result.value));
}

void test_get_token_close_brace() {
    char *input = "}";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(close_brace, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("}", result.value));
}

void test_get_token_constant() {
    char *input = "1";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(constant, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("1", result.value));
}

void test_get_token_semicolon() {
    char *input = ":";
    struct token result = get_token(&input);

    TEST_ASSERT_EQUAL(semicolon, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp(":", result.value));
}

void test_get_token_undefined() {
    char *input = "";
    struct token result = get_token(&input);
    TEST_ASSERT_EQUAL(undefined, result.token_type);
}

void test_get_tokens() {
    char *input = "int main\n";
    struct linked_list *result = get_tokens(input);
    struct node *p = result->head;
    TEST_ASSERT_EQUAL(keyword, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "int"));
    p = p->next;
    TEST_ASSERT_EQUAL(identifier, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "main"));
    TEST_ASSERT_NULL(p->next);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_get_token_keyword);
    RUN_TEST(test_get_token_identifier);
    RUN_TEST(test_get_token_open_parenthesis);
    RUN_TEST(test_get_token_close_parenthesis);
    RUN_TEST(test_get_token_open_brace);
    RUN_TEST(test_get_token_close_brace);
    RUN_TEST(test_get_token_constant);
    RUN_TEST(test_get_token_semicolon);
    RUN_TEST(test_get_token_undefined);
    RUN_TEST(test_get_tokens);
    return UNITY_END();
}
