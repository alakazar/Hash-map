#ifndef HASHMAP_H
#define HASHMAP_H
#include "stack.h"
#include "tree.h"

typedef struct {
    int size;
    Tree* tree;
} Map;


int hash(const char* name);
    

Map* createHM();

void displayHashMap(Tree* a);

void display(Map* a);

KdPlayer* getHM(Map* a, char* name);

int sizeHM(Map* a);

int removeHM(Map* a, char*name);

int addHM(Map* a, KdPlayer e);

int update(Map* a,char* name,int kills,int deaths);

Stack * findStack(Stack *stack, char *key);

Stack * findTree(Tree *node, char *key, int hash);

int freeHM(Map* a);

void freeMap(Map* hmap);




#endif 