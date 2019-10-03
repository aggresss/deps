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
static Node* TreeMinimum(Node* curnode);
static Node* TreeSuccessor(Node* curnode);

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

static Node* TreeSuccessor(Node* curnode)
{
    if (curnode->child[RIGHT])
        curnode = TreeMinimum(curnode->child[RIGHT]);
    else
    {
        Node* curparent = curnode->parent;
        while (curparent && curnode == curparent->child[RIGHT])
        {
            curnode = curparent;
            curparent = curparent->parent;
        }
        curnode = curparent;
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

Node* TreeFind(Tree* aTree, void* content)
{
    int result = 0;
    Node* curnode = aTree->root;

    while (curnode)
    {
        result = aTree->compare(curnode->content, content);
        if (result == 0) {
            break;
        } else {
            curnode = curnode->child[result > 0];
        }
    }
    return curnode;
}

void* TreeRemoveNode(Tree* aTree, Node* curnode)
{
    Node* redundant = curnode;
    Node* curchild = NULL;
    size_t size = curnode->size;
    void* content = curnode->content;

    /* if the node to remove has 0 or 1 children, it can be removed without involving another node */
    if (curnode->child[LEFT] && curnode->child[RIGHT]) /* 2 children */
        redundant = TreeSuccessor(curnode);     /* now redundant must have at most one child */

    curchild = redundant->child[(redundant->child[LEFT] != NULL) ? LEFT : RIGHT];
    if (curchild) /* we could have no children at all */
        curchild->parent = redundant->parent;

    if (redundant->parent == NULL)
        aTree->root = curchild;
    else
    {
        if (redundant == redundant->parent->child[LEFT])
            redundant->parent->child[LEFT] = curchild;
        else
            redundant->parent->child[RIGHT] = curchild;
    }

    if (redundant != curnode)
    {
        curnode->content = redundant->content;
        curnode->size = redundant->size;
    }

    if (isBlack(redundant))
    {
        if (curchild == NULL)
        {
            if (redundant->parent)
            {
                Node temp;
                memset(&temp, '\0', sizeof(Node));
                temp.parent = redundant->parent;
                temp.red = 0;
                TreeBalanceAfterRemove(aTree, &temp, index);
            }
        }
        else
            TreeBalanceAfterRemove(aTree, curchild, index);
    }

    free(redundant);

    if (index == 0)
    {
        aTree->size -= size;
        --(aTree->count);
    }
    return content;
}

