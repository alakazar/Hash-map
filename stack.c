#include "stack.h"

/**
 * @brief Creates a new stack node with the given player and initializes its fields.
 * 
 * This function allocates memory for a new stack node, sets its element with the given player,
 * and initializes its next pointer to NULL.
 * 
 * @param e The player to be associated with the stack node.
 * @return A pointer to the newly created stack node.
 */
Stack* createStack(KdPlayer e) {
    Stack* n = NULL;
    n = malloc(sizeof(Stack));
    if (n == NULL) {
        exit(1);
    }
    n->elmt = e;
    n->next = NULL;
    return n;
}

/**
 * @brief Inserts a player into the stack while maintaining the stack property.
 * 
 * This function inserts a player into the stack by creating a new stack node and
 * setting its next pointer to the current top of the stack.
 * 
 * @param stack The current top of the stack.
 * @param e The player to be inserted.
 * @return The updated top of the stack.
 */
Stack* insertStack(Stack* stack, KdPlayer e) {
    if (stack == NULL) {
        exit(2);
    }
    Stack* n = createStack(e);
    n->next = stack;
    return n;
}

/**
 * @brief Displays the contents of the stack.
 * 
 * This function iterates through the stack, printing the name, kills, and deaths
 * of each player in the stack.
 * 
 * @param a The top of the stack.
 */
void displayStack(Stack* a) {
    while (a != NULL) {
        printf("    --    name: %s    --\n", a->elmt.name);
        printf("    --    %d kills    --\n", a->elmt.kills);
        printf("    --    %d deaths    --\n\n", a->elmt.deaths);
        a = a->next;
    }
}

/**
 * @brief Retrieves a player from the stack with the specified name.
 * 
 * This function searches for a player in the stack with the specified name.
 * If found, a pointer to the player is returned; otherwise, NULL is returned.
 * 
 * @param a The top of the stack.
 * @param name The name of the player to search for.
 * @return A pointer to the player in the stack.
 */
KdPlayer* getStack(Stack* a, char* name) {
    while (a != NULL) {
        if (strcmp(name, a->elmt.name) == 0) {
            return &(a->elmt);
        }
        a = a->next;
    }
    return NULL;
}

/**
 * @brief Deletes a player from the stack while maintaining the stack property.
 * 
 * This function removes a player from the stack with the specified name. The
 * stack property is maintained by adjusting the next pointers accordingly.
 * 
 * @param stack The top of the stack.
 * @param player The player to be removed.
 * @return The updated top of the stack.
 */
Stack* deleteStack(Stack* stack, KdPlayer* player) { 
    if (stack == NULL) {
        return NULL;
    }
    if (strcmp(stack->elmt.name, player->name) == 0) {
        Stack* tmp = stack;
        stack = stack->next;
        free(tmp);
        return stack;
    }

    Stack *p = stack;
    while (p->next != NULL) {
        if (strcmp(p->next->elmt.name, player->name) == 0) {
            Stack *temp = p->next;
            p->next = temp->next;
            free(temp);
            return stack;
        }
        p = p->next;
    }
    return stack;
}

/**
 * @brief Finds a stack node with the specified name in the stack.
 * 
 * This function searches for a stack node with the specified name in the stack.
 * If found, a pointer to the stack node is returned; otherwise, NULL is returned.
 * 
 * @param stack The top of the stack.
 * @param name The name of the player to search for.
 * @return A pointer to the stack node with the specified name.
 */
Stack * findStack(Stack *stack, char *name) {
    Stack *p = stack;
    while (p != NULL) {
        if (strcmp(p->elmt.name, name) == 0) {
            return stack;
        }
        p = p->next;
    }
    return NULL;
}

/**
 * @brief Frees the memory allocated for the stack.
 * 
 * This function iterates through the stack, freeing the memory allocated for each
 * stack node.
 * 
 * @param stack The top of the stack.
 */
void freeStack(Stack* stack) {
    while (stack != NULL) {
        Stack* temp = stack;
        stack = stack->next;
        free(temp);
    }
}
