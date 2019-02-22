
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define ASSERT_SUCCESS (0)
#define ASSERT_FAIL    (1)

int main(void)
{
    int ret = ASSERT_FAIL;
    char * test_buff = NULL;
    char expect_cjson_string[] = "{\"number\":1}";
    cJSON *root = NULL;
    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "number", 1.0);
    test_buff = cJSON_PrintUnformatted(root);
    if (test_buff) {
        ret = strncmp(test_buff, expect_cjson_string, strlen(expect_cjson_string));
        printf("output: %s\n", test_buff);

        /* Must be free buffer after print */
        free(test_buff);
    }
    cJSON_Delete(root);

    return ret;
}
