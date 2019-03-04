#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mbuf.h"

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();


static void test_mbuf_alloc(void)
{

}

static void test_mbuf_alloc_ref(void)
{

}

static void test_mbuf_init(void)
{

}

static void test_mbuf_reset(void)
{

}

static void test_mbuf_resize(void)
{

}

static void test_mbuf_trim(void)
{

}

static void test_mbuf_shift(void)
{

}

static void test_mbuf_write_mem(void)
{

}

static void test_mbuf_write_u8(void)
{

}

static void test_mbuf_write_u16(void)
{

}

static void test_mbuf_write_u32(void)
{

}

static void test_mbuf_write_u64(void)
{

}

static void test_mbuf_write_str(void)
{

}

static void test_mbuf_read_mem(void)
{

}

static void test_mbuf_read_u8(void)
{

}

static void test_mbuf_read_u16(void)
{

}

static void test_mbuf_read_u32(void)
{

}

static void test_mbuf_read_u64(void)
{

}

static void test_mbuf_read_str(void)
{

}

static void test_mbuf_strdup(void)
{

}

static void test_mbuf_write_pl_skip(void)
{

}

static void test_mbuf_fill(void)
{

}

int main(void)
{
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
