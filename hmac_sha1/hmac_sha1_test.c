#include <stdio.h>
#include <string.h>
#include "hmac_sha1.h"

/*
 * Verification result generate from
 * https://www.liavaag.org/English/SHA-Generator/HMAC/
 * http://tool.oschina.net/encrypt?type=2
 *
 * */

#define ASSERT_SUCCESS (0)
#define ASSERT_FAIL    (-1)

int main(void) {
    int i;
    int len = 0;
    char sec_key[] = "deps";
    char data[] = "aggresss";
    char out[SHA1_DIGEST_SIZE] = {0};
    char out_hexstr[SHA1_DIGEST_SIZE * 2 + 1] = {0};
    char expect_hmacsha1_result[] = "b8cf05a896659c144efd03b6d3c00b42eb32faae";

    hmac_sha1(sec_key, strlen(sec_key), data, strlen(data), out, &len);
    for(i = 0; i< 20; i++) {
        sprintf((char *)(out_hexstr + i * 2), "%02x", *(unsigned char *)(out + i));
    }
    printf("data: %s\nkey: %s\nHMAC-SHA1: %s\n", data, sec_key, out_hexstr);

    return strcmp(expect_hmacsha1_result, out_hexstr);
}

