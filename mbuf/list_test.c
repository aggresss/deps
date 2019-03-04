#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();


static void test_list_init(void)
{

}

static void test_list_flush(void)
{

}

static void test_list_clear(void)
{

}

static void test_list_append(void)
{

}

static void test_list_prepend(void)
{

}

static void test_list_insert_before(void)
{

}

static void test_list_insert_after(void)
{

}

static void test_list_unlink(void)
{

}

static void test_list_sort(void)
{

}

static void test_list_apply(void)
{

}

static void test_list_head(void)
{

}

static void test_list_tail(void)
{

}

static void test_list_count(void)
{

}

int main(void)
{
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
