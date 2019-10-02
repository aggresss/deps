#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEFT 0
#define RIGHT 1
#if !defined(max)
#define max(a,b) (((a)>(b))?(a):(b))
#endif


static int isRed(Node* aNode);
static int isBlack(Node* aNode);

static void TreeRotate(Tree* aTree, Node* curnode, int direction);
static Node* TreeBAASub(Tree* aTree, Node* curnode, int which, int index);
static void TreeBalanceAfterAdd(Tree* aTree, Node* curnode, int index);
static void* TreeAddByIndex(Tree* aTree, void* content, size_t size, int index);
static Node* TreeFindIndex1(Tree* aTree, void* key, int index, int value);
static Node* TreeFindContentIndex(Tree* aTree, void* key, int index);
static Node* TreeMinimum(Node* curnode);

static Node* TreeNextElementIndex(Tree* aTree, Node* curnode, int index);
static Node* TreeBARSub(Tree* aTree, Node* curnode, int which, int index);
static void TreeBalanceAfterRemove(Tree* aTree, Node* curnode, int index);
static void* TreeRemoveIndex(Tree* aTree, void* content, int index);




static int isRed(Node* aNode)
{
    return (aNode != NULL) && (aNode->red);
}


static int isBlack(Node* aNode)
{
    return (aNode == NULL) || (aNode->red == 0);
}

static void TreeRotate(Tree* aTree, Node* curnode, int direction)
{
    Node* other = curnode->child[!direction];

    curnode->child[!direction] = other->child[direction];
    if (other->child[direction] != NULL)
        other->child[direction]->parent = curnode;
    other->parent = curnode->parent;
    if (curnode->parent == NULL) {
        aTree->root = other;
    } else if (curnode == curnode->parent->child[direction]) {
        curnode->parent->child[direction] = other;
    } else {
        curnode->parent->child[!direction] = other;
    }

    other->child[direction] = curnode;
    curnode->parent = other;
}

static Node* TreeMinimum(Node* curnode)
{
    if (curnode)
        while (curnode->child[LEFT]) {
            curnode = curnode->child[LEFT];
        }
    return curnode;
}


Tree* TreeInit(int(*compare)(void*, void*, int))
{
    Tree* newt = malloc(sizeof(Tree));
    memset(newt, '\0', sizeof(Tree));
    return newt;
}

void TreeFree(Tree* aTree)
{
    if (aTree) {
        free(aTree);
    }
}


