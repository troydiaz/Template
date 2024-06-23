
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

/*
 * This structure represents a single node in a AVL tree.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains the `key`
 * field representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the AVL should be ordered based on this `key` field.
 * It also contains a `height` field that represents the height of the node

 * You should not modify this structure.
 */

struct avl_node
{
    int key;
    int height;
    struct avl_node *left;
    struct avl_node *right;
    struct avl_node *parent;
};

/*
 * This structure represents an entire AVL tree.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct avl_tree
{
    struct avl_node* root;
};

/*
 * This function should allocate and initialize a new, empty, AVL tree and return
 * a pointer to it.
 */
struct avl_tree* avl_create() {
    struct avl_tree* avl = malloc(sizeof(struct avl_tree));
    assert(avl);
    avl->root = NULL;
    return avl;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 */
void avl_remove(struct avl_tree* avl, int key) {
    assert(avl);
    avl->root = _avl_subtree_remove(avl->root, key);
}

/*
 * This function should insert a new node with key into the AVL tree. 
 */
void avl_insert(struct avl_tree* avl, int key) {
    assert(avl);
    avl->root = _avl_subtree_insert(avl->root, key);
}

/*
 * This function should free the memory associated with a AVL tree.  While this
 * function should up all memory used in the AVL tree itself, it should not free
 * any memory allocated to the pointer values stored in the AVL tree.  This is the
 * responsibility of the caller.
 *
 */
void avl_free(struct avl_tree* avl) {
    assert(avl);
    while (avl->root != NULL) {
        avl_remove(avl, avl->root->key);
    }

    free(avl);
}


 
/* A helper function to get the height of the tree */
int height(struct avl_node *node){
    if (node == NULL)
        return -1;
    return node->height;
}
 
/* A helper function to get maximum of two integers */
int max(int a, int b){
    return (a > b)? a : b;
}


/* Get Balance factor of node N */
int getBalance(struct avl_node *node){
    if (node == NULL)
        return -1;
    return height(node->right) - height(node->left);
}

/* A helper function for pre-order tree traversal */
void _preOrder_helper (struct avl_node *root){
    if(root != NULL){
        printf("%d ", root->key);
        _preOrder_helper(root->left);
        _preOrder_helper(root->right);
    }
    return;
}

/* A helper function to print preorder traversal of the tree. */
void preOrder(struct avl_tree *avl){
    _preOrder_helper(avl->root);
    return;
}


/*
 * Helper function to return the leftmost node within a subtree of a AVL tree.
 */
struct avl_node* _avl_subtree_leftmost_node(struct avl_node* n) {
    while (n->left != NULL) {
        n = n->left;
    }
    return n;
}


/*
 * Helper function to remove a given key from a subtree of a BST rooted at
 * a specified node.
 */
struct avl_node* _avl_subtree_remove(struct avl_node* n, int key) {
    if (n == NULL) 
        return NULL;
     
    else if (key < n->key) {
        n->left = _avl_subtree_remove(n->left, key);
        return n;
    } 

    else if (key > n->key) {
        n->right = _avl_subtree_remove(n->right, key);
        return n;
    }


    if (n->left != NULL && n->right != NULL) {
        struct avl_node* in_order_succ = _avl_subtree_leftmost_node(n->right);
        n->key = in_order_succ->key;
        n->right = _avl_subtree_remove(n->right, in_order_succ->key);
        return n;
    } 

    else if (n->left != NULL) {
        struct avl_node* left_child = n->left;
        free(n);
        return left_child;
    } 
    
    else if (n->right != NULL) {
        struct avl_node* right_child = n->right;
        free(n);
        return right_child;
    } 

    else {
        free(n);
        return NULL;
    }
}


 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct avl_node* _avl_node_create(int key){
    struct avl_node* node = malloc(sizeof(struct avl_node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 0;  // new node is inserted at leaf, height is 0
    return node;
}


struct avl_node *rebalance(struct avl_node *N){
    if (getBalance(N) < -1){
        if (getBalance(N->left) > 0){
            N->left = leftRotate(N->left);
        }
        struct avl_node* newSubtreeRoot = rightRotate(N);
        if (newSubtreeRoot->parent != NULL){
            if (newSubtreeRoot->parent != NULL){
                if (newSubtreeRoot->parent->left == N){
                    newSubtreeRoot->parent->left = newSubtreeRoot;
                }
                else{
                    newSubtreeRoot->parent->right = newSubtreeRoot;
                }
            }
        }
    }
    else if (getBalance(N) > 1){
        if (getBalance(N->right) < 0){
            N->right = rightRotate(N->right);
        }
        struct avl_node* newSubtreeRoot = leftRotate(N);
        if (newSubtreeRoot->parent != NULL){
            if (newSubtreeRoot->parent != NULL){
                if (newSubtreeRoot->parent == N){
                    newSubtreeRoot->parent->left = newSubtreeRoot;
                }
                else{
                    newSubtreeRoot->parent->right = newSubtreeRoot;
                }
            }
        }
    }
    else{
        N->height = 1 + max(height(N->left), height(N->right));
    }
    
}

/*****************************************************
 *  You need to modify the following three functions
 *****************************************************/

/* A function to right rotate subtree rooted with N */
struct avl_node *rightRotate(struct avl_node *N){
    
    // If N is left heavy

    // The node to be rotated
    struct avl_node* child = N->left;

    // Replace left child with right
    N->left = child->right;

    // If there is a left child, update it to be N's parent
    if (N->left != NULL){
        N->left->parent = N;
    }

    // Move N down
    child->right = N;

    // Reconnect childs parent to N's parent
    child->parent = N->parent;

    // Set N's parent to be child
    N->parent = child;

    // Update height of N and child
    N->height = 1 + max(height(N->left), height(N->right));

    child->height = 1 + max(height(child->left), height(child->right));

    // Return pointer to child
    return child;
}


 

/* A function to left rotate subtree rooted with N */
struct avl_node *leftRotate(struct avl_node *N){
    
    // If N is right heavy

    struct avl_node* child = N->right;

    N->right = child->left;

    if (N->right != NULL){
        N->right->parent = N;
    }

    child->left = N;

    child->parent = N->parent;

    N->parent = child;

    N->height = 1 + max(height(N->left), height(N->right));

    child->height = 1 + max(height(child->left), height(child->right));
    
    return child;
    
}
 

 
/* Recursive function to insert a key in the subtree rooted
 * with node and returns the new root of the subtree.
 */
struct avl_node* _avl_subtree_insert(struct avl_node* node, int key){
    /* normal BST insertion */
    /* Note: you may also want to modify the provided insertion function */

    // Base case that node is null and creates a new node with key
    if (node == NULL)
        return _avl_node_create(key);
    
    // Recursively insert in left subtree
    if (key < node->key){
    	node->left = _avl_subtree_insert(node->left, key);
        node->left->parent = node;
    }
    // Recursively insert in right subtree
    else if (key > node->key){
        node->right = _avl_subtree_insert(node->right, key);
    	node->right->parent = node;
    }
    // Return pointer to current node
    else{
        return node;
    }

    /*
     * FIXME: check the height, apply single/double rotations when needed
     *        to maintain a height-balanced tree
     */

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Get balance
    int balance = getBalance(node);

    // LL, if balance factor is < -1 and key is less than key of left child, perform right rotation on current node
    if (balance < -1 && key < node->left->key){
        return rightRotate(node);
    }

    // RR, if balance factor is > 1 and key is greater than right child's key, perform left rotate
    if (balance > 1 && key > node->right->key){
        return leftRotate(node);
    }

    // LR, left rotation on left child, and then right rotation on current node
    if (balance < -1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL, right rotation on right child, and then left rotation on current node
    if (balance > 1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return updated node
    return node;    
}

