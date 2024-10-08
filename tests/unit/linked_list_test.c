#include <stdlib.h>

#include "../../src/linked_list.h"
#include "../../unity/src/unity.h"

void setUp() {}

void tearDown() {}

void test_add_empty_list() {
    struct linked_list list;
    list.head = NULL;
    char *value = "value";
    int status = add(&list, value);

    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL_STRING("value", list.head->val);
}

void test_add_non_empty_list() {
    struct linked_list list;
    list.head = NULL;

    char *value = "value";
    struct node *node = malloc(sizeof(struct node));
    node->val = value;
    list.head = node;

    int status = add(&list, value);

    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_NOT_NULL(list.head);
    TEST_ASSERT_NOT_NULL(list.head->next);
    TEST_ASSERT_EQUAL_STRING("value", list.head->next->val);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_add_empty_list);
    RUN_TEST(test_add_non_empty_list);
    return UNITY_END();
}
