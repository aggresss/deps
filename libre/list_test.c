#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "mem.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

static void test_list_ledata(void)
{
    // setup
     struct list test_list = LIST_INIT;
     struct le test_le1 = LE_INIT;
     struct le test_le2 = LE_INIT;
     char data_le1[] = "foo";
     char data_le2[] = "bar";

     // assertion
     list_append(&test_list, &test_le1, data_le1);
     list_append(&test_list, &test_le2, data_le2);

     assert(0 == strcmp(list_ledata(&test_le1), "foo"));
     assert(0 == strcmp(list_ledata(&test_le2), "bar"));

     // teardown
     list_clear(&test_list);
}

static void test_list_contains(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "foo";
    char data_le2[] = "bar";

    // assertion
    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);

    assert(list_contains(&test_list, &test_le1));
    assert(list_contains(&test_list, &test_le2));

    // teardown
    list_clear(&test_list);
}

static void test_list_isempty(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "foo";
    char data_le2[] = "bar";

    // assertion
    assert(list_isempty(&test_list));
    list_append(&test_list, &test_le1, data_le1);
    assert(!list_isempty(&test_list));
    list_append(&test_list, &test_le2, data_le2);
    assert(!list_isempty(&test_list));

    // teardown
    list_clear(&test_list);

}

static void test_list_init(void)
{
    struct list test_list;
    list_init(&test_list);
    assert(test_list.head == NULL);
    assert(test_list.tail == NULL);
}

static void test_list_flush(void)
{
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    struct le test_le3 = LE_INIT;
    struct le test_le4 = LE_INIT;
    void * test_data = mem_zalloc(256, NULL);

    list_append(&test_list, &test_le1, mem_ref(test_data));
    list_prepend(&test_list, &test_le2, mem_ref(test_data));
    list_insert_before(&test_list, &test_le2, &test_le3, mem_ref(test_data));
    list_insert_after(&test_list, &test_le2, &test_le4, mem_ref(test_data));

    list_flush(&test_list);
    assert(test_list.head == NULL);
    assert(test_list.tail == NULL);

    // teardown
    mem_deref(test_data);

}

static void test_list_clear(void)
{
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    void * test_data = mem_zalloc(256, NULL);

    list_append(&test_list, &test_le1, test_data);

    list_clear(&test_list);
    assert(test_list.head == NULL);
    assert(test_list.tail == NULL);

    // teardown
    mem_deref(test_data);
}

static void test_list_append(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "foo";
    char data_le2[] = "bar";

    // assertion
    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);

    assert(0 == strcmp(test_le1.next->data, "bar"));
    assert(0 == strcmp(test_le2.prev->data, "foo"));

    // teardown
    list_clear(&test_list);

}

static void test_list_prepend(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "foo";
    char data_le2[] = "bar";

    // assertion
    list_prepend(&test_list, &test_le2, data_le2);
    list_prepend(&test_list, &test_le1, data_le1);

    assert(0 == strcmp(test_le1.next->data, "bar"));
    assert(0 == strcmp(test_le2.prev->data, "foo"));

    // teardown
    list_clear(&test_list);
}

static void test_list_insert_before(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "foo";
    char data_le2[] = "bar";

    // assertion
    list_append(&test_list, &test_le2, data_le2);
    list_insert_before(&test_list, &test_le2, &test_le1, data_le1);

    assert(0 == strcmp(test_le1.next->data, "bar"));
    assert(0 == strcmp(test_le2.prev->data, "foo"));

    // teardown
    list_clear(&test_list);
}

static void test_list_insert_after(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "foo";
    char data_le2[] = "bar";

    // assertion
    list_append(&test_list, &test_le1, data_le1);
    list_insert_after(&test_list, &test_le1, &test_le2, data_le2);

    assert(0 == strcmp(test_le1.next->data, "bar"));
    assert(0 == strcmp(test_le2.prev->data, "foo"));

    // teardown
    list_clear(&test_list);
}

static void test_list_unlink(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    struct le test_le3 = LE_INIT;
    struct le test_le4 = LE_INIT;
    char data_le1[] = "zhang3";
    char data_le2[] = "li4";
    char data_le3[] = "wang5";
    char data_le4[] = "zhao6";

    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);
    list_append(&test_list, &test_le3, data_le3);
    list_append(&test_list, &test_le4, data_le4);

    // assertion
    list_unlink(&test_le2);
    assert(test_le2.list == NULL);
    assert(test_le2.prev == NULL);
    assert(test_le2.next == NULL);
    assert(0 == strcmp(test_le1.next->data, "wang5"));
    assert(0 == strcmp(test_le3.prev->data, "zhang3"));

    // teardown
    list_clear(&test_list);
}

static bool test_sort_h(struct le *le1, struct le *le2, void *arg)
{
    (void)arg;
    return strlen(le1->data) < strlen(le2->data) ? true : false;
}

static void test_list_sort(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    struct le test_le3 = LE_INIT;
    struct le test_le4 = LE_INIT;
    char data_le1[] = "abcd";
    char data_le2[] = "ab";
    char data_le3[] = "a";
    char data_le4[] = "abc";
    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);
    list_append(&test_list, &test_le3, data_le3);
    list_append(&test_list, &test_le4, data_le4);

    // assertion
    list_sort(&test_list, test_sort_h, NULL);
    assert(0 == strcmp(list_head(&test_list)->data, "a"));
    assert(0 == strcmp(list_head(&test_list)->next->data, "ab"));
    assert(0 == strcmp(list_head(&test_list)->next->next->data, "abc"));
    assert(0 == strcmp(list_head(&test_list)->next->next->next->data, "abcd"));

    // teardown
    list_clear(&test_list);
}

static bool test_apply_h(struct le *le, void *arg)
{
    return strlen(le->data) ? false : true;
}

static void test_list_apply(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    struct le test_le3 = LE_INIT;
    struct le test_le4 = LE_INIT;
    char data_le1[] = "zhang3";
    char data_le2[] = "li4";
    char data_le3[] = "";
    char data_le4[] = "zhao6";
    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);
    list_append(&test_list, &test_le3, data_le3);
    list_append(&test_list, &test_le4, data_le4);

    // assertion
    assert(0 == strlen(list_apply(&test_list, true, test_apply_h, NULL)->data));

    // teardown
    list_clear(&test_list);
}

static void test_list_head(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "zhang3";
    char data_le2[] = "li4";
    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);

    // assertion
    assert(0 == strcmp(list_head(&test_list)->data, "zhang3"));

    // teardown
    list_clear(&test_list);
}

static void test_list_tail(void)
{
    // setup
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    char data_le1[] = "zhang3";
    char data_le2[] = "li4";
    list_append(&test_list, &test_le1, data_le1);
    list_append(&test_list, &test_le2, data_le2);

    // assertion
    assert(0 == strcmp(list_tail(&test_list)->data, "li4"));

    // teardown
    list_clear(&test_list);
}

static void test_list_count(void)
{
    // setup
    int n = 0;
    struct list test_list = LIST_INIT;
    struct le test_le1 = LE_INIT;
    struct le test_le2 = LE_INIT;
    struct le test_le3 = LE_INIT;
    struct le test_le4 = LE_INIT;
    char data_le1[] = "zhang3";
    char data_le2[] = "li4";
    char data_le3[] = "wang5";
    char data_le4[] = "zhao6";

    // assertion
    list_append(&test_list, &test_le1, data_le1);
    assert(++n == list_count(&test_list));
    list_append(&test_list, &test_le2, data_le2);
    assert(++n == list_count(&test_list));
    list_append(&test_list, &test_le3, data_le3);
    assert(++n == list_count(&test_list));
    list_append(&test_list, &test_le4, data_le4);
    assert(++n == list_count(&test_list));

    // teardown
    list_clear(&test_list);
}

int main(void)
{
  test(list_ledata);
  test(list_contains);
  test(list_isempty);

  test(list_init);
  test(list_flush);
  test(list_clear);
  test(list_append);
  test(list_prepend);
  test(list_insert_before);
  test(list_insert_after);
  test(list_unlink);
  test(list_sort);
  test(list_apply);
  test(list_head);
  test(list_tail);
  test(list_count);

  puts("... \x1b[32m100%\x1b[0m\n");
  return 0;
}
