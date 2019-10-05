#include "rbtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, const char * argv[])
{
    int rc = 0;
    int *ip = NULL;
    Tree* t = TreeInit(TreeIntCompare);



    ip = malloc(sizeof(int));
    *ip = 2;
    replaced = TreeAdd(t, (void*) ip, sizeof(int));
}

