#include "hashMap.h"

/**
 * @brief Computes the hash value for the given name.
 * 
 * This function calculates the hash value for the given name using a simple algorithm.
 * It sums up the ASCII values of each character in the name and multiplies it by the
 * ASCII value of the first character.
 * 
 * @param name The name for which the hash value is to be computed.
 * @return The computed hash value.
 */
int hash(const char* name) {
    if (name == NULL || name[0] == '\0') {
        exit(2);
    }
    int hash = 0;
    int firstChar = (int)name[0];

    for (int i = 0; name[i] != '\0'; ++i) {
        hash += (int)name[i];
    }
    return hash = hash * firstChar;
}

/**
 * @brief Creates a new HashMap and initializes its fields.
 * 
 * This function allocates memory for a new HashMap, sets its size to 0, and initializes
 * its tree pointer to NULL.
 * 
 * @return A pointer to the newly created HashMap.
 */
Map* createHM() {
    Map* hmap = malloc(sizeof(Map));
    if (hmap == NULL) {
        exit(1);
    }
    hmap->size = 0;
    hmap->tree = NULL;
    return hmap;
}

/**
 * @brief Displays the contents of the HashMap.
 * 
 * This function recursively displays the hash, stack, and tree structure of each node
 * in the HashMap.
 * 
 * @param a The root of the tree.
 */
void displayHashMap(Tree* a) {
    if (a != NULL) {
        printf("\nhash : %d\n", a->hash);
        displayStack(a->stack);
        displayHashMap(a->ls);
        displayHashMap(a->rs);
    }
}

/**
 * @brief Displays the contents of the HashMap.
 * 
 * This function displays the entire contents of the HashMap by calling the recursive
 * displayHashMap function.
 * 
 * @param a The HashMap to be displayed.
 */
void display(Map* a) {
    displayHashMap(a->tree);
}

/**
 * @brief Retrieves a player from the HashMap with the specified name.
 * 
 * This function computes the hash value for the given name, then searches for the player
 * in the HashMap using the findTree function. If found, a pointer to the player is returned;
 * otherwise, NULL is returned.
 * 
 * @param a The HashMap.
 * @param name The name of the player to search for.
 * @return A pointer to the player in the HashMap.
 */
KdPlayer* getHM(Map* a, char* name) {
    int h = hash(name); 
    Stack *s = findTree(a->tree, name, h);
    if (s == NULL) {
        return NULL;
    }
    return &(s->elmt);
}

/**
 * @brief Retrieves the size of the HashMap.
 * 
 * This function returns the size of the HashMap, indicating the number of players
 * currently stored in it.
 * 
 * @param a The HashMap.
 * @return The size of the HashMap.
 */
int sizeHM(Map* a) {
    return a->size;
}

/**
 * @brief Removes a player from the HashMap.
 * 
 * This function removes a player with the specified name from the HashMap. The player
 * is removed from the corresponding tree node's stack, and if the stack becomes empty,
 * the tree node is deleted.
 * 
 * @param a The HashMap.
 * @param name The name of the player to be removed.
 * @return 1 if the removal is successful, 0 otherwise.
 */
int removeHM(Map* a, char* name) {
    KdPlayer* playerToRemove = getHM(a, name);

    if (playerToRemove == NULL) {
        return 0;
    }

    Tree* treeContainingPlayer = getTree(a->tree, playerToRemove->hash);

    if (treeContainingPlayer == NULL) {
        return 0; 
    }

    treeContainingPlayer->stack = deleteStack(treeContainingPlayer->stack, playerToRemove);

    if (treeContainingPlayer->stack == NULL) {
        a->tree = deleteTree(a->tree, treeContainingPlayer);
    }

    a->size = a->size - 1;
    return 1;
}

/**
 * @brief Adds a player to the HashMap.
 * 
 * This function inserts a new player into the HashMap. If the tree structure
 * is successfully updated, the size of the HashMap is incremented.
 * 
 * @param a The HashMap.
 * @param e The player to be added.
 * @return 1 if the addition is successful, 0 otherwise.
 */
int addHM(Map* a, KdPlayer e) {
    Tree* newTree = insertTree(a->tree, e);
    if (newTree != NULL) {
        a->tree = newTree;
        a->size++;
        return TRUE;  
    } else {
        return FALSE;
    }
}

/**
 * @brief Updates the kills and deaths of a player in the HashMap.
 * 
 * This function updates the kills and deaths of a player in the HashMap
 * with the specified name. If the player is not found, the function returns 0.
 * 
 * @param a The HashMap.
 * @param name The name of the player to be updated.
 * @param newKills The new number of kills.
 * @param newDeaths The new number of deaths.
 * @return 1 if the update is successful, 0 otherwise.
 */
int update(Map* a, char* name, int newKills, int newDeaths) {
    KdPlayer *player = getHM(a, name);
    if (player == NULL) {
        return FALSE;
    }
    player->kills = newKills;
    player->deaths = newDeaths;
    return TRUE;
}

/**
 * @brief Frees the memory allocated for the HashMap.
 * 
 * This function frees the memory allocated for the HashMap, including all its
 * tree nodes and associated stacks.
 * 
 * @param hmap The HashMap to be freed.
 */
void freeMap(Map* hmap) {
    if (hmap != NULL) {
        freeTree(hmap->tree);
        free(hmap);
    }
}
