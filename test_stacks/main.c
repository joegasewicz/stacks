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
    free(s1->options);
    free(s1->nodes);
    free(s1);
}

static void test_S_Stack_push2(void **state)
{
    // Test multiple nodes
    S_Options options = (S_Options){ .max_length = 3, .dynamic = false };
    Stack *s1 = S_Stack_new(&options);
    assert_int_equal(s1->length, 0);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    S_Stack_push(s1, &data1);
    S_Stack_push(s1, &data2);
    S_Stack_push(s1, &data3);
    assert_int_equal(s1->length, 3);
    assert_ptr_equal(s1->nodes->data, &data3);
    assert_ptr_equal(s1->nodes->link->data, &data2);
    assert_ptr_equal(s1->nodes->link->link->data, &data1);
    // test max_length
    int res4 = S_Stack_push(s1, &data4);
    assert_int_equal(res4, S_OUT_OF_BOUNDS_ERROR);
    S_Stack_destroy(s1);
}

static void test_S_Stack_pop(void **state)
{
    Stack *s1 = S_Stack_new(NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    S_Stack_push(s1, &data1);
    assert_int_equal(s1->length, 1);
    S_Stack_push(s1, &data2);
    assert_int_equal(s1->length, 2);
    S_Stack_push(s1, &data3);
    assert_int_equal(s1->length, 3);
    void* res3 = S_Stack_pop(s1);
    assert_int_equal(s1->length, 2);
    assert_ptr_equal(res3, &data3);
    assert_ptr_equal(s1->nodes->data, &data2);
    void* res2 = S_Stack_pop(s1);
    assert_int_equal(s1->length, 1);
    assert_ptr_equal(res2, &data2);
    void* res1 = S_Stack_pop(s1);
    assert_int_equal(s1->length, 0);
    assert_ptr_equal(res1, &data1);
    assert_null(s1->nodes);
    S_Stack_destroy(s1);
}

static void test_S_SIZE(void **state)
{
    Stack *s1 = S_Stack_new(NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    S_Stack_push(s1, &data1);
    int r1 = S_SIZE(s1);
    assert_int_equal(r1, 1);
    S_Stack_push(s1, &data2);
    int r2 = S_SIZE(s1);
    assert_int_equal(r2, 2);
    S_Stack_push(s1, &data3);
    int r3 = S_SIZE(s1);
    assert_int_equal(r3, 3);
    S_Stack_destroy(s1);
}

static void test_S_CURRENT_INDEX(void **state)
{
    Stack *s1 = S_Stack_new(NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    S_Stack_push(s1, &data1);
    int r1 = S_CURRENT_INDEX(s1);
    assert_int_equal(r1, 0);
    S_Stack_push(s1, &data2);
    int r2 = S_CURRENT_INDEX(s1);
    assert_int_equal(r2, 1);
    S_Stack_push(s1, &data3);
    int r3 = S_CURRENT_INDEX(s1);
    assert_int_equal(r3, 2);
    S_Stack_destroy(s1);
}

static void test_S_PEEK(void **state)
{
    Stack *s1 = S_Stack_new(NULL);
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    S_Stack_push(s1, &data1);
    void *d1 = S_PEEK(s1);
    assert_ptr_equal(d1, &data1);
    S_Stack_push(s1, &data2);
    void *d2 = S_PEEK(s1);
    assert_ptr_equal(d2, &data2);
    S_Stack_push(s1, &data3);
    void *d3 = S_PEEK(s1);
    assert_ptr_equal(d3, &data3);
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
            cmocka_unit_test(test_S_Stack_push2),
            cmocka_unit_test(test_S_Stack_pop),
            cmocka_unit_test(test_S_SIZE),
            cmocka_unit_test(test_S_CURRENT_INDEX),
            cmocka_unit_test(test_S_PEEK)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
