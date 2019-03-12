#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mem.h"
#include "mbuf.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

// inline function test

static void test_mbuf_buf(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    uint8_t * get_buf = mbuf_buf(test_mbuf);
    assert(get_buf == test_mbuf->buf);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_get_left(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    mbuf_set_pos(test_mbuf, 5);
    mbuf_set_end(test_mbuf, 20);
    assert(mbuf_get_left(test_mbuf) == 15);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_get_space(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    mbuf_set_pos(test_mbuf, 5);
    assert(mbuf_get_space(test_mbuf) == 251);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_set_end(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    mbuf_set_end(test_mbuf, 5);
    assert(test_mbuf->pos == 0);
    assert(test_mbuf->end == 5);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_advance(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    mbuf_advance(test_mbuf, 5);
    assert(test_mbuf->pos == 5);
    assert(test_mbuf->end == 0);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_rewind(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    mbuf_set_pos(test_mbuf, 5);
    mbuf_set_end(test_mbuf, 20);
    mbuf_rewind(test_mbuf);
    assert(test_mbuf->pos == 0);
    assert(test_mbuf->end == 0);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_skip_to_end(void)
{

}

static void test_mbuf_alloc(void)
{

    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    assert(test_mbuf != NULL);
    assert(test_mbuf->buf != NULL);
    assert(test_mbuf->size == 256);
    assert(test_mbuf->pos == 0);
    assert(test_mbuf->end == 0);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_alloc_ref(void)
{
    struct mbuf * test_mbuf = NULL, *test_mbuf_ref = NULL;
    test_mbuf = mbuf_alloc(256);
    test_mbuf_ref = mbuf_alloc_ref(test_mbuf);
    assert(test_mbuf_ref != NULL);
    assert(test_mbuf->buf == test_mbuf_ref->buf);
    assert(mem_nrefs(test_mbuf->buf) == 2);

    // teardown
    mem_deref(test_mbuf_ref);
    mem_deref(test_mbuf);

}

static void test_mbuf_init(void)
{
    struct mbuf test_mbuf;
    memset(&test_mbuf, 1, sizeof(struct mbuf));
    mbuf_init(&test_mbuf);
    assert(test_mbuf.buf == NULL);
    assert(test_mbuf.size == 0);
    assert(test_mbuf.pos == 0);
    assert(test_mbuf.end == 0);
}

static void test_mbuf_reset(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    mbuf_reset(test_mbuf);
    assert(test_mbuf->buf == NULL);
    assert(test_mbuf->size == 0);
    assert(test_mbuf->pos == 0);
    assert(test_mbuf->end == 0);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_resize(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    assert(mbuf_resize(test_mbuf, 1024) == 0);
    assert(test_mbuf->buf != NULL);
    assert(test_mbuf->pos == 0);
    assert(test_mbuf->end == 0);
    assert(test_mbuf->size == 1024);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_trim(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_str[] = "1234567890";
    mbuf_write_mem(test_mbuf, (uint8_t *) test_str, sizeof(test_str));

    // assertion
    mbuf_set_end(test_mbuf, 2);
    mbuf_trim(test_mbuf);
    assert(test_mbuf->size == 2);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_shift(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_str[] = "123456789";
    mbuf_write_mem(test_mbuf, (uint8_t *) test_str, sizeof(test_str));

    // assertion
    mbuf_shift(test_mbuf, 10);
    assert(test_mbuf->end == 20);
    assert(test_mbuf->pos == 20);
    mbuf_shift(test_mbuf, (-5));
    assert(test_mbuf->end == 15);
    assert(test_mbuf->pos == 15);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_mem(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    char test_str[] = "123456789";
    assert(
            mbuf_write_mem(test_mbuf, (uint8_t * )test_str, sizeof(test_str))
                    == 0);
    assert(test_mbuf->end == sizeof(test_str));
    assert(test_mbuf->pos == sizeof(test_str));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_u8(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    uint8_t test_u8 = 1;
    assert(mbuf_write_u8(test_mbuf, test_u8) == 0);
    assert(test_mbuf->end == sizeof(test_u8));
    assert(test_mbuf->pos == sizeof(test_u8));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_u16(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    uint16_t test_u16 = 1;
    assert(mbuf_write_u16(test_mbuf, test_u16) == 0);
    assert(test_mbuf->end == sizeof(test_u16));
    assert(test_mbuf->pos == sizeof(test_u16));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_u32(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    uint32_t test_u32 = 1;
    assert(mbuf_write_u32(test_mbuf, test_u32) == 0);
    assert(test_mbuf->end == sizeof(test_u32));
    assert(test_mbuf->pos == sizeof(test_u32));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_u64(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    uint64_t test_u64 = 1;
    assert(mbuf_write_u64(test_mbuf, test_u64) == 0);
    assert(test_mbuf->end == sizeof(test_u64));
    assert(test_mbuf->pos == sizeof(test_u64));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_str(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    char * test_str = "123456789";
    assert(mbuf_write_str(test_mbuf, test_str) == 0);
    assert(test_mbuf->end == strlen(test_str));
    assert(test_mbuf->pos == strlen(test_str));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_write_pl(void)
{
    // setup
    char test_str[] = "123456789";
    struct pl test_pl;
    test_pl.p = test_str;
    test_pl.l = sizeof(test_str);
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    assert(mbuf_write_pl(test_mbuf, &test_pl) == 0);
    assert(test_mbuf->end == sizeof(test_str));
    assert(test_mbuf->pos == sizeof(test_str));

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_read_mem(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_str[] = "123456789";
    char comp_str[sizeof(test_str)] = { 0 };
    mbuf_write_mem(test_mbuf, (uint8_t *) test_str, sizeof(test_str));
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    mbuf_read_mem(test_mbuf, (uint8_t *) comp_str, sizeof(test_str));
    assert(strcmp(test_str, comp_str) == 0);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_read_u8(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_uint8 = 1;
    char comp_uint8 = 0;
    mbuf_write_u8(test_mbuf, test_uint8);
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    comp_uint8 = mbuf_read_u8(test_mbuf);
    assert(test_uint8 == comp_uint8);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_read_u16(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_uint16 = 1;
    char comp_uint16 = 0;
    mbuf_write_u16(test_mbuf, test_uint16);
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    comp_uint16 = mbuf_read_u16(test_mbuf);
    assert(test_uint16 == comp_uint16);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_read_u32(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_uint32 = 1;
    char comp_uint32 = 0;
    mbuf_write_u32(test_mbuf, test_uint32);
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    comp_uint32 = mbuf_read_u32(test_mbuf);
    assert(test_uint32 == comp_uint32);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_read_u64(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_uint64 = 1;
    char comp_uint64 = 0;
    mbuf_write_u64(test_mbuf, test_uint64);
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    comp_uint64 = mbuf_read_u64(test_mbuf);
    assert(test_uint64 == comp_uint64);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_read_str(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char * test_str = "123456789";
    char comp_str[10] = { 0 };
    mbuf_write_str(test_mbuf, test_str);
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    mbuf_read_str(test_mbuf, comp_str, strlen(test_str));
    assert(strcmp(test_str, comp_str) == 0);

    // teardown
    mem_deref(test_mbuf);
}

static void test_mbuf_strdup(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char * test_str = "1234567890";
    char * comp_str = NULL;
    mbuf_write_str(test_mbuf, test_str);
    mbuf_set_pos(test_mbuf, 0);
    // assertion
    mbuf_strdup(test_mbuf, &comp_str, 10);
    assert(strcmp(test_str, comp_str) == 0);

    // teardown
    mem_deref(comp_str);
    mem_deref(test_mbuf);
}

static void test_mbuf_write_pl_skip(void)
{
    // setup
    char test_str[] = "123456789";
    struct pl test_pl, skip_pl;
    test_pl.p = test_str;
    test_pl.l = sizeof(test_str);
    skip_pl.p = test_str + 1;
    skip_pl.l = 2;
    char * comp_str = NULL;
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);

    // assertion
    assert(mbuf_write_pl_skip(test_mbuf, &test_pl, &skip_pl) == 0);
    assert(test_mbuf->end == 8);
    assert(test_mbuf->pos == 8);
    mbuf_set_pos(test_mbuf, 0);
    mbuf_strdup(test_mbuf, &comp_str, 8);
    assert(strcmp("1456789", comp_str) == 0);

    // teardown
    mem_deref(comp_str);
    mem_deref(test_mbuf);
}

static void test_mbuf_fill(void)
{
    // setup
    struct mbuf * test_mbuf = NULL;
    test_mbuf = mbuf_alloc(256);
    char test_str[10] = {0};
    char comp_str[sizeof(test_str)] = { 0 };
    memset(comp_str, 'c', sizeof(test_str));

    // assertion
    mbuf_fill(test_mbuf, 'c', sizeof(test_str));
    mbuf_set_pos(test_mbuf, 0);
    mbuf_read_mem(test_mbuf, (uint8_t *) test_str, sizeof(test_str));
    assert(memcmp(test_str, comp_str, sizeof(test_str)) == 0);

    // teardown
    mem_deref(test_mbuf);
}

int main(void)
{
    test(mbuf_buf);
    test(mbuf_get_left);
    test(mbuf_get_space);
    test(mbuf_set_end);
    test(mbuf_advance);
    test(mbuf_rewind);
    test(mbuf_skip_to_end);

    test(mbuf_alloc);
    test(mbuf_alloc_ref);
    test(mbuf_init);
    test(mbuf_reset);
    test(mbuf_resize);
    test(mbuf_trim);
    test(mbuf_shift);
    test(mbuf_write_mem);
    test(mbuf_write_u8);
    test(mbuf_write_u16);
    test(mbuf_write_u32);
    test(mbuf_write_u64);
    test(mbuf_write_str);
    test(mbuf_write_pl);
    test(mbuf_read_mem);
    test(mbuf_read_u8);
    test(mbuf_read_u16);
    test(mbuf_read_u32);
    test(mbuf_read_u64);
    test(mbuf_read_str);
    test(mbuf_strdup);
    test(mbuf_write_pl_skip);
    test(mbuf_fill);

    puts("... \x1b[32m100%\x1b[0m\n");
    return 0;
}
