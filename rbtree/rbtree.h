#if !defined(TREE_H)
#define TREE_H

#include <stdlib.h> /* for size_t definition */

/**
 * Structure to hold all data for one list element
 */
typedef struct NodeStruct {
    struct NodeStruct *parent;   /**< pointer to parent tree node, in case we need it */
    struct NodeStruct *child[2]; /**< pointers to child tree nodes 0 = left, 1 = right */
    void* content;               /**< pointer to element content */
    size_t size;                 /**< size of content */
    unsigned int red : 1;
} Node;


/**
 * Structure to hold all data for one tree
 */
typedef struct {
    Node *root;                     /**< root node pointer */
    int (*compare)(void*, void*);   /**< comparison function */
    int count;                      /**< no of items */
    size_t size;                    /**< heap storage used */
} Tree;


Tree* TreeInit(int(*compare)(void*, void*));

void TreeFree(Tree* aTree);

void* TreeAdd(Tree* aTree, void* content, size_t size);

void* TreeRemove(Tree* aTree, void* content);

Node* TreeFind(Tree* aTree, void* content);

Node* TreeSuccessor(Tree* aTree, Node* curnode);

#endif

