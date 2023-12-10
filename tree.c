#include "tree.h"

/**
 * @brief Checks if the given tree node has a left child.
 * 
 * This function checks if the given tree node has a left child.
 * 
 * @param a The tree node.
 * @return 1 if the tree node has a left child, 0 otherwise.
 */
int leftChild(Tree *a) {
    return a->ls != NULL ? 1 : 0;
}

/**
 * @brief Checks if the given tree node has a right child.
 * 
 * This function checks if the given tree node has a right child.
 * 
 * @param a The tree node.
 * @return 1 if the tree node has a right child, 0 otherwise.
 */
int rightChild(Tree *a) {
    return a->rs != NULL ? 1 : 0;
}

/**
 * @brief Creates a new tree node and initializes its fields.
 * 
 * This function allocates memory for a new tree node, sets its hash,
 * initializes its stack using the provided player, and sets its left
 * and right children to NULL.
 * 
 * @param e The player for which the tree node is created.
 * @return A pointer to the newly created tree node.
 */
Tree* createTree(KdPlayer e) {
    Tree* n = NULL;
    n = malloc(sizeof(Tree));
    if (n == NULL) {
        exit(1);
    }
    n->hash = e.hash;
    n->stack = createStack(e);
    n->ls = NULL;
    n->rs = NULL;
    return n;
}

/**
 * @brief Inserts a player into the tree structure.
 * 
 * This function inserts a player into the tree structure. If the tree is
 * empty, a new tree node is created. If the hash of the player matches the
 * hash of the current tree node, the player is inserted into the stack of
 * that node. If the hash is less than the current node's hash, the player is
 * inserted into the left subtree, and if it's greater, it's inserted into
 * the right subtree.
 * 
 * @param a The root of the tree.
 * @param e The player to be inserted.
 * @return The root of the updated tree.
 */
Tree* insertTree(Tree* a, KdPlayer e) {
    if (a == NULL) {
        return createTree(e);
    } else if (a->hash == e.hash) {
        a->stack = insertStack(a->stack, e);
    } else if (a->hash > e.hash) {
        a->ls = insertTree(a->ls, e);
    } else if (a->hash < e.hash) {
        a->rs = insertTree(a->rs, e);
    }
    return a;
}

/**
 * @brief Retrieves a tree node with a specified hash value.
 * 
 * This function searches for a tree node with the specified hash value
 * in the tree structure. If found, a pointer to the tree node is returned;
 * otherwise, NULL is returned.
 * 
 * @param a The root of the tree.
 * @param e The hash value to search for.
 * @return A pointer to the tree node with the specified hash.
 */
Tree* getTree(Tree* a, int e) {
    if (a == NULL) {
        return NULL;
    } else if (a->hash == e) {
        return a;
    } else if (a->hash > e) {
        return getTree(a->ls, e);
    } else {
        return getTree(a->rs, e);
    }
}

/**
 * @brief Deletes the maximum node in the subtree.
 * 
 * This function deletes the maximum node in the subtree rooted at the
 * given tree node. The hash and stack of the maximum node are copied to
 * the node to be removed, and the maximum node is then deleted.
 * 
 * @param a The root of the subtree.
 * @param toRemove The node to be removed.
 * @return The root of the updated subtree.
 */
Tree* deleteMax(Tree* a, Tree* toRemove) {
    Tree* tmp = NULL;
    if (toRemove == NULL) {
        exit(1);
    }
    if (rightChild(a)) {
        a->rs = deleteMax(a->rs, toRemove);
    } else {
        toRemove->hash = a->hash;
        toRemove->stack = a->stack;
        tmp = a;
        a = a->ls;
        free(tmp);
    }
    return a;
}

/**
 * @brief Deletes a tree node with a specified hash value.
 * 
 * This function deletes a tree node with the specified hash value from
 * the tree structure. If the node has no left child, it is replaced by
 * its right child. If the node has no right child, it is replaced by its
 * left child. If the node has both left and right children, it is replaced
 * by the maximum node in its left subtree.
 * 
 * @param a The root of the tree.
 * @param toRemove The node to be removed.
 * @return The root of the updated tree.
 */
Tree* deleteTree(Tree* a, Tree* toRemove) {
    Tree* tmp = NULL;
    if (toRemove == NULL) {
        exit(1);
    }
    int h = toRemove->hash;

    if (a == NULL) {
        return a;
    } else if (h > a->hash) {
        a->rs = deleteTree(a->rs, toRemove);
    } else if (h < a->hash) {
        a->ls = deleteTree(a->ls, toRemove);
    } else if (a->ls == NULL) {
        tmp = a;
        a = a->rs;
        free(tmp);
    } else {
        a->ls = deleteMax(a->ls, toRemove);
    }
    return a;
}

/**
 * @brief Finds a player in the tree structure with a specified name and hash.
 * 
 * This function searches for a player with the specified name and hash in the
 * tree structure. If found, a pointer to the player's stack is returned; otherwise,
 * NULL is returned.
 * 
 * @param node The root of the tree.
 * @param name The name of the player to search for.
 * @param hash The hash value of the player's name.
 * @return A pointer to the player's stack.
 */
Stack* findTree(Tree* node, char* name, int hash) {
    if (node == NULL) {
        return NULL;
    }
    if (hash == node->hash) {
        Stack* stack = node->stack;
        return findStack(stack, name);
    }
    if (hash < node->hash) {
        return findTree(node->ls, name, hash);
    }
    if (hash > node->hash) {
        return findTree(node->rs, name, hash);
    }
    return NULL;
}

/**
 * @brief Frees the memory allocated for the tree structure.
 * 
 * This function recursively frees the memory allocated for the tree structure,
 * including all its nodes and associated stacks.
 * 
 * @param tree The root of the tree.
 */
void freeTree(Tree* tree) {
    if (tree != NULL) {
        freeTree(tree->ls);
        freeTree(tree->rs);
        freeStack(tree->stack);
        free(tree);
    }
}
