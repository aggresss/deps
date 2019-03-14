#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mem.h"
#include "list.h"
#include "hash.h"

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

/* reference: http://www.kjson.com/encrypt/hash/?fm=map */
/* foobar => f952fde7 */
/* FooBar => a56c3788 */

static void test_hash_joaat(void)
{
    char test_str_1[] = "FooBar";
    char test_str_2[] = "foobar";
    uint32_t calc_val_1 = hash_joaat((uint8_t *)test_str_1, sizeof(test_str_1) - 1);
    assert(calc_val_1 == 0xa56c3788);

    uint32_t calc_val_2 = hash_joaat((uint8_t *)test_str_2, sizeof(test_str_2) - 1);
    assert(calc_val_2 == 0xf952fde7);
}

static void test_hash_joaat_ci(void)
{
    char test_str_1[] = "FooBar";
    char test_str_2[] = "foobar";
    uint32_t calc_val_1 = hash_joaat_ci(test_str_1, sizeof(test_str_1) - 1);
    uint32_t calc_val_2 = hash_joaat_ci(test_str_2, sizeof(test_str_2) - 1);
    assert(calc_val_1 == calc_val_2);
}

static void test_hash_joaat_str(void)
{
    char test_str_1[] = "FooBar";
    char test_str_2[] = "foobar";
    uint32_t calc_val_1 = hash_joaat_str(test_str_1);
    assert(calc_val_1 == 0xa56c3788);

    uint32_t calc_val_2 = hash_joaat_str(test_str_2);
    assert(calc_val_2 == 0xf952fde7);
}

static void test_hash_joaat_str_ci(void)
{
    char * test_str_1 = "FooBar";
    char * test_str_2 = "foobar";
    uint32_t calc_val_1 = hash_joaat_str_ci(test_str_1);
    uint32_t calc_val_2 = hash_joaat_str_ci(test_str_2);
    assert(calc_val_1 == calc_val_2);
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
