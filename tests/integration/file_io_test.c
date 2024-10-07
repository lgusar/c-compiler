#include "../../src/file_io.h"
#include "../../unity/src/unity.h"

void setUp() {}

void tearDown() {}

void test_read_file() {
    char *result;
    char *filename = "tests/integration/test.c";
    int status = read_from_file(filename, &result);
    TEST_ASSERT_EQUAL(0, status);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_read_file);
    return UNITY_END();
}
