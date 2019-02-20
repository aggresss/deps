#include "flag.h"

int main(int argc, const char * argv[])
{
    int n = 0;
    flag_int(&n, "num", "Number of requests");
    flag_parse(argc, argv, "test libghttp");
    printf("%d\n", n);
    return 0;
}

