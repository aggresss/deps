
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urlsafe_b64.h"

#define ASSERT_SUCCESS (0)
#define ASSERT_FAIL    (1)

/*
 * Verification result generate from
 * http://tool.oschina.net/encrypt?type=3
 *
 * */

int main(void)
{
    size_t out_len = 1024;
    char data[] = "https://github.com/aggresss/deps/blob/master/b64/README.md";
    char buff[1024] = {0};
    char expect_b64_string[] = "aHR0cHM6Ly9naXRodWIuY29tL2FnZ3Jlc3NzL2RlcHMvYmxvYi9tYXN0ZXIvYjY0L1JFQURNRS5tZA==";

    out_len = urlsafe_b64_encode(data, strlen(data), buff, out_len);
    if (out_len != strlen(expect_b64_string))
        exit(EXIT_FAILURE);
    if (0 != strncmp(buff, expect_b64_string, strlen(expect_b64_string)))
        exit(EXIT_FAILURE);

    return EXIT_SUCCESS;
}
