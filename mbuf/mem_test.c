
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mem.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();


// Tests

static void test_mem_alloc()
{
    void * test_mem = mem_alloc(256, NULL);
    assert(test_mem != NULL);
    assert(sizeof(test_mem) == 256);
}

static void test_mem_zalloc()
{

}

static void test_mem_realloc()
{

}

static void test_mem_reallocarray()
{

}

static void test_mem_ref()
{

}

static void test_mem_deref()
{

}

static void test_mem_nrefs()
{

}

static void test_mem_get_stat()
{

}


int main(void)
{
  test(mem_alloc);
  test(mem_zalloc);
  test(mem_realloc);
  test(mem_reallocarray);
  test(mem_ref);
  test(mem_deref);
  test(mem_nrefs);
  test(mem_get_stat);

  puts("... \x1b[32m100%\x1b[0m\n");
  return 0;
}
