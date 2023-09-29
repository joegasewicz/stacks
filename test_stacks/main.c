#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>
#include "../stacks.h"

static void null_test_success(void **state)
{
    (void) state;
}


static void test_S_Stack_new(void **state)
{
    S_Options *options = malloc(sizeof(S_Options));
    options->max_length = 100;
    Stack *s = S_Stack_new(options);
    assert_int_equal(s->options->max_length, 100);
    assert_int_equal(s->options->dynamic, false);
    // Test with max_length 0
    S_Options *options2 = malloc(sizeof(S_Options));
    options2->max_length = 0;
    Stack *s2 = S_Stack_new(options2);
    assert_int_equal(s2->options->max_length, 0);
    // Test with no options
    Stack *s3 = S_Stack_new(NULL);
    assert_int_equal(s3->options->max_length, 0);
    assert_int_equal(s3->options->dynamic, true);
    free(options);
    free(options2);
    free(s->options);
    free(s);
    free(s2->options);
    free(s2);
    free(s3->options);
    free(s3);
}

static void test_S_Stack_destroy(void **state)
{
    Stack *s1 = S_Stack_new(NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    S_Stack_push(s1, &data1);
    S_Stack_push(s1, &data2);
    S_Stack_push(s1, &data3);
    int res1 = S_Stack_destroy(s1);
    assert_int_equal(res1, S_OK);
}

static void test_S_Stack_push1(void **state)
{
    // Test Single node
    Stack *s1 = S_Stack_new(NULL);
    assert_int_equal(s1->options->max_length, 0);
    assert_int_equal(s1->options->dynamic, true);
    int data1 = 1;
    S_Stack_push(s1, &data1);
    assert_non_null(s1->nodes);
    assert_ptr_equal(s1->nodes->data, &data1);
    assert_int_equal(s1->nodes->index, 0);
    assert_null(s1->nodes->link);
    assert_int_equal(s1->length, 1);
    assert_int_equal(s1->curr_index, 0);
    assert_int_equal(s1->top_index, 0);
    free(s1->options);
    free(s1->nodes);
    free(s1);
}

static void test_S_Stack_push2(void **state)
{
    // Test multiple nodes
    Stack *s1 = S_Stack_new(NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    S_Stack_push(s1, &data1);
    S_Stack_push(s1, &data2);
    S_Stack_push(s1, &data3);
    assert_ptr_equal(s1->nodes->data, &data3);
    assert_ptr_equal(s1->nodes->link->data, &data2);
    assert_ptr_equal(s1->nodes->link->link->data, &data1);
    S_Stack_destroy(s1);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
            cmocka_unit_test(null_test_success),
            cmocka_unit_test(test_S_Stack_destroy),
            cmocka_unit_test(test_S_Stack_new),
            cmocka_unit_test(test_S_Stack_push1),
            cmocka_unit_test(test_S_Stack_push2)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
