#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mem.h"
#include "list.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

// inline function test

static void test_hash_alloc(void)
{

}

static void test_hash_append(void)
{

}

static void test_hash_unlink(void)
{

}

static void test_hash_lookup(void)
{

}

static void test_hash_apply(void)
{

}

static void test_hash_list(void)
{

}

static void test_hash_bsize(void)
{

}

static void test_hash_flush(void)
{

}

static void test_hash_clear(void)
{

}

static void test_hash_valid_size(void)
{

}

// http://www.kjson.com/encrypt/hash/?fm=map

static void test_hash_joaat(void)
{

}

static void test_hash_joaat_ci(void)
{

}

static void test_hash_joaat_str(void)
{

}

static void test_hash_joaat_str_ci(void)
{

}

static void test_hash_joaat_pl(void)
{

}

static void test_hash_joaat_pl_ci(void)
{

}

static void test_hash_fast(void)
{

}

static void test_hash_fast_str(void)
{

}


int main(void)
{
    test(hash_alloc);
    test(hash_append);
    test(hash_unlink);
    test(hash_lookup);
    test(hash_apply);
    test(hash_list);
    test(hash_bsize);
    test(hash_flush);
    test(hash_clear);
    test(hash_valid_size);

    test(hash_joaat);
    test(hash_joaat_ci);
    test(hash_joaat_str);
    test(hash_joaat_str_ci);
    test(hash_joaat_pl);
    test(hash_joaat_pl_ci);
    test(hash_fast);
    test(hash_fast_str);

    puts("... \x1b[32m100%\x1b[0m\n");
    return 0;
}
