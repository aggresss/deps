#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mem.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

static int test_dh_callback = 0;
static void dh_cb_func(void *data)
{
    test_dh_callback++;
}

// Tests

static void test_mem_alloc()
{
    void * test_mem = NULL;
    test_mem = mem_alloc(256, dh_cb_func);
    assert(test_mem != NULL);
    mem_deref(test_mem);
    assert(test_dh_callback == 1);
}

static void test_mem_zalloc()
{
    int i;
    void * test_mem = NULL;
    test_mem = mem_zalloc(256, NULL);
    assert(test_mem != NULL);
    for(i = 0; i < 256; i++) {
        assert(*(uint8_t *)(test_mem + i) == 0);
    }
    mem_deref(test_mem);
}

static void test_mem_realloc()
{
    // setup
    void * test_mem = NULL;
    test_mem = mem_alloc(256, NULL);
    assert(test_mem != NULL);

    // assertions
    test_mem = mem_realloc(test_mem, 1);
    assert(test_mem != NULL);
    test_mem = mem_realloc(test_mem, 1024);
    assert(test_mem != NULL);

    // teardown
    mem_deref(test_mem);
}

static void test_mem_reallocarray()
{
    void * test_mem = NULL;
    test_mem = mem_reallocarray(test_mem, 16, 16, NULL);
    assert(test_mem != NULL);
    test_mem = mem_reallocarray(test_mem, 8, 8, NULL);
    assert(test_mem != NULL);
    mem_deref(test_mem);
}

static void test_mem_ref()
{
    // setup
    void * test_mem = NULL;
    test_mem = mem_alloc(256, NULL);
    assert(test_mem != NULL);

    // assertions
    void * assert_mem = mem_ref(test_mem);
    assert(assert_mem == test_mem);
    assert(2 == mem_nrefs(test_mem));
    mem_deref(test_mem);

    // teardown
    mem_deref(test_mem);
}

static void test_mem_deref()
{
    // setup
    void * test_mem = NULL;
    test_mem = mem_alloc(256, NULL);
    assert(test_mem != NULL);

    // assertions
    void * assert_mem = mem_ref(test_mem);
    assert(assert_mem == test_mem);

    assert(NULL == mem_deref(test_mem));
    assert(1 == mem_nrefs(test_mem));

    // teardown
    mem_deref(test_mem);
}

static void test_mem_nrefs()
{
    // setup
    int i;
    void * test_mem = NULL;
    test_mem = mem_alloc(256, NULL);
    assert(test_mem != NULL);

    // assertions
    for(i = 1; i <= 10; i++) {
        assert(i == mem_nrefs(test_mem));
        mem_ref(test_mem);
    }
    for(i = 10; i >= 1; i--) {
        mem_deref(test_mem);
        assert(i == mem_nrefs(test_mem));
    }

    // teardown
    mem_deref(test_mem);
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

  puts("... \x1b[32m100%\x1b[0m\n");
  return 0;
}
