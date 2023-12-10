#ifndef TREE_H
#define TREE_H
#include "stack.h"

typedef struct Tree {
    int hash;
    struct Tree* ls;
    struct Tree* rs;
    struct Stack* stack;
} Tree;

int leftChild(Tree* a);

int rightChild(Tree *a);

Tree* createTree(KdPlayer e);

Tree* insertTree(Tree* a, KdPlayer e);

Tree* getTree(Tree* a, int e);

Tree * deleteMax(Tree* a,Tree*);

Tree * deleteTree(Tree *a,Tree *);

Stack * findStack(Stack *stack, char *name);

int deleteMaxTree(Tree* a);

void freeTree(Tree* tree);



#endif