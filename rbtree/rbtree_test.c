#include "rbtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int traverse(Tree *t, int lookfor)
{
    Node* curnode = NULL;
    int rc = 0;

    printf("Traversing\n");
    curnode = TreeNextElement(t, curnode);
    /* printf("content int %d\n", *(int*)(curnode->content)); */
    while (curnode) {
        Node* prevnode = curnode;

        curnode = TreeNextElement(t, curnode);
        /* if (curnode)
         printf("content int %d\n", *(int*)(curnode->content)); */
        if (prevnode && curnode && (*(int*) (curnode->content) < *(int*) (prevnode->content))) {
            printf("out of order %d < %d\n", *(int*) (curnode->content), *(int*) (prevnode->content));
        }
        if (curnode && (lookfor == *(int*) (curnode->content)))
            printf("missing item %d actually found\n", lookfor);
    }
    printf("End traverse %d\n", rc);
    return rc;
}

int main(int argc, const char * argv[])
{
    int rc = 0;
    int *ip = NULL;
    Tree* t = TreeInit(TreeIntCompare);

    ip = malloc(sizeof(int));
    *ip = 2;
    TreeAdd(t, (void*) ip, sizeof(int));
    ip = malloc(sizeof(int));
    *ip = 3;
    TreeAdd(t, (void*) ip, sizeof(int));

    traverse(t, 2);

    traverse(t, 3);

    traverse(t, 4);
}

