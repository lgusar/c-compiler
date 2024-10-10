#include <string.h>

#include "../src/token.h"
#include "../unity/src/unity.h"

void setUp() {}

void tearDown() {}

void test_get_token_int() {
    char *input = "int";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(k_int, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("int", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_return() {
    char *input = "return";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(k_return, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("return", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_void() {
    char *input = "void";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(k_void, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("void", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_identifier() {
    char *input = "main";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(identifier, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("main", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_open_parenthesis() {
    char *input = "(";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(open_parenthesis, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("(", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_close_parenthesis() {
    char *input = ")";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(close_parenthesis, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp(")", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_open_brace() {
    char *input = "{";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(open_brace, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("{", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_close_brace() {
    char *input = "}";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(close_brace, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("}", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_constant() {
    char *input = "1";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(constant, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp("1", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_semicolon() {
    char *input = ";";
    struct token result;
    int status = get_token(&input, &result);

    TEST_ASSERT_EQUAL(semicolon, result.token_type);
    TEST_ASSERT_EQUAL(0, strcmp(";", result.value));
    TEST_ASSERT_EQUAL(0, status);
}

void test_get_token_invalid() {
    char *input = "@";
    struct token result;
    int status = get_token(&input, &result);
    TEST_ASSERT_EQUAL(undefined, result.token_type);
    TEST_ASSERT_EQUAL(-1, status);
}

void test_get_tokens() {
    char *input = "int main\n";

    struct linked_list *result = linked_list_init();
    int status = get_tokens(input, result);

    TEST_ASSERT_EQUAL(0, status);

    struct node *p = result->head;
    TEST_ASSERT_EQUAL(k_int, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "int"));
    p = p->next;
    TEST_ASSERT_EQUAL(identifier, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "main"));
    TEST_ASSERT_NULL(p->next);
}

void test_get_tokens_multiple_lines() {
    char *input = "int main() {\n\n}";

    struct linked_list *result = linked_list_init();
    int status = get_tokens(input, result);

    TEST_ASSERT_EQUAL(0, status);

    struct node *p = result->head;
    TEST_ASSERT_EQUAL(k_int, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "int"));
    p = p->next;

    TEST_ASSERT_EQUAL(identifier, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "main"));
    p = p->next;

    TEST_ASSERT_EQUAL(open_parenthesis, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "("));
    p = p->next;

    TEST_ASSERT_EQUAL(close_parenthesis, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, ")"));
    p = p->next;

    TEST_ASSERT_EQUAL(open_brace, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "{"));
    p = p->next;

    TEST_ASSERT_EQUAL(close_brace, ((struct token *)p->val)->token_type);
    TEST_ASSERT_EQUAL(0, strcmp(((struct token *)p->val)->value, "}"));
    TEST_ASSERT_NULL(p->next);
}

void test_get_tokens_all_token_types() {
    char *input = "int main(void) {\n\treturn 2;\n}";

    struct linked_list *result = linked_list_init();
    int status = get_tokens(input, result);

    TEST_ASSERT_EQUAL(0, status);
}

void test_get_tokens_ignore_singe_line_comment() {
    char *input = "//int main void";

    struct linked_list *result = linked_list_init();
    int status = get_tokens(input, result);

    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_NULL(result->head);
}

void test_get_tokens_ignore_multiline_comment() {
    char *input = "/* this is a multiline comment\nthis is the second line */int main";

    struct linked_list *result = linked_list_init();
    int status = get_tokens(input, result);

    TEST_ASSERT_EQUAL(0, status);
}

void test_get_tokens_multiline_comment_without_end_backslash() {
    char *input = "/* this is a multiline comment\nthis is the second line *";

    struct linked_list *result = linked_list_init();
    int status = get_tokens(input, result);

    TEST_ASSERT_EQUAL(0, status);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_get_token_int);
    RUN_TEST(test_get_token_return);
    RUN_TEST(test_get_token_void);
    RUN_TEST(test_get_token_identifier);
    RUN_TEST(test_get_token_open_parenthesis);
    RUN_TEST(test_get_token_close_parenthesis);
    RUN_TEST(test_get_token_open_brace);
    RUN_TEST(test_get_token_close_brace);
    RUN_TEST(test_get_token_constant);
    RUN_TEST(test_get_token_semicolon);
    RUN_TEST(test_get_token_invalid);
    RUN_TEST(test_get_tokens);
    RUN_TEST(test_get_tokens_multiple_lines);
    RUN_TEST(test_get_tokens_all_token_types);
    RUN_TEST(test_get_tokens_ignore_singe_line_comment);
    RUN_TEST(test_get_tokens_ignore_multiline_comment);
    RUN_TEST(test_get_tokens_multiline_comment_without_end_backslash);
    return UNITY_END();
}
