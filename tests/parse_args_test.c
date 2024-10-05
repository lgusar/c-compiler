#include <assert.h>
#include <getopt.h>

#include "../unity/src/unity.h"

#include "../src/parse_args.h"

void setUp() {}

void tearDown() {
    /* reset getopt */
    optind = 1;
}

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

void test_lex_and_parameter() {
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

void test_parse_and_parameter() {
    int argc = 3;
    char *argv[] = {"parse_args", "--parse", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(1, to_parse);
}

void test_codegen_and_parameter() {
    int argc = 3;
    char *argv[] = {"parse_args", "--codegen", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(1, to_codegen);
}

void test_two_options_and_parameter() {
    int argc = 4;
    char *argv[] = {"parse_args", "--lex", "--parse", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(1, ret);
}

void test_multiple_options_and_parameter() {
    int argc = 5;
    char *argv[] = {"parse_args", "--lex", "--parse", "--codegen", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    TEST_ASSERT_EQUAL(1, ret);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_no_required_parameter);
    RUN_TEST(test_required_parameter);
    RUN_TEST(test_lex_and_parameter);
    RUN_TEST(test_parse_and_parameter);
    RUN_TEST(test_codegen_and_parameter);
    RUN_TEST(test_two_options_and_parameter);
    RUN_TEST(test_multiple_options_and_parameter);
    return UNITY_END();
}
