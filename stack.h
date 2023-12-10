#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int hash;
    char name[10];
    int kills;
    int deaths;
} KdPlayer;

typedef struct Stack {
    KdPlayer elmt;
    struct Stack* next;
} Stack;


Stack* createStack(KdPlayer e);

Stack* insertStack(Stack* stack, KdPlayer e);

void displayStack(Stack* a);

KdPlayer* getStack(Stack* a, char* name);

Stack* deleteStack(Stack* stack, KdPlayer* player);

int deleteAllStack(Stack* a);

void freeStack(Stack* stack);





#endif 