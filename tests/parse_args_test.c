#include <assert.h>
#include <stdio.h>

#include "../unity/src/unity.h"

#include "../src/parse_args.h"

void setUp() {}

void tearDown() {}

void test_required_parameter() {
    int argc = 2;
    char *argv[] = {"parse_args", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(0, ret);
}

void test_no_required_parameter() {
    int argc = 1;
    char *argv[] = {"parse_args"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(1, ret);
}

void test_one_option_and_parameter() {
    int argc = 3;
    char *argv[] = {"parse_args", "--lex", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(1, to_lex);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_required_parameter);
    RUN_TEST(test_no_required_parameter);
    RUN_TEST(test_one_option_and_parameter);
    return UNITY_END();
}
