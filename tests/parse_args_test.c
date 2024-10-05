#include <assert.h>
#include <stdio.h>

#include "../src/parse_args.h"

void test_required_parameter() {
    int argc = 2;
    char *argv[] = {"parse_args", "a.c"};
    char *filename;

    int to_lex = 0;
    int to_parse = 0;
    int to_codegen = 0;
    int *flags[] = {&to_lex, &to_parse, &to_codegen};

    int ret = parse_args(argc, argv, &filename, flags);

    assert(ret == 0);
    printf("test_required_parameter passed\n"); 
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

    assert(ret == 1);
    printf("test_no_required_parameter passed\n"); 
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

    assert(ret == 0);
    assert(to_lex == 1);
    printf("test_one_option_and_parameter passed\n"); 
}

int main() {
    printf("STARTING TESTS\n\n");
    test_required_parameter();
    test_required_parameter();
    test_no_required_parameter();
    test_one_option_and_parameter();
    printf("ALL TESTS SUCCESSFUL\n\n");
    return 0;
}
