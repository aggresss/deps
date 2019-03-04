#include "stdlib.h"
#include "flag.h"

int main(int argc, const char * argv[])
{
    int n = 0;
    flag_int(&n, "num", "Number of requests");
    flag_parse(argc, argv, "test libghttp");

    if (n == 0) {
        exit(EXIT_FAILURE);
    }

    return 0;
}

