#ifndef __AVL_H
#define __AVL_H 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Structure used to represent an AVL tree node, and an entire AVL tree.
 */

struct avl_node;
struct avl_tree;


/* 
 * Function Prototypes:
 */
int height(struct avl_node *node);
int max(int a, int b);
int getBalance(struct avl_node *node);

void _preOrder_helper (struct avl_node* node);
void preOrder(struct avl_tree *avl);

struct avl_tree* avl_create();
void avl_free(struct avl_tree* avl);
void avl_insert(struct avl_tree* avl, int key);
void avl_remove(struct avl_tree* avl, int key);

struct avl_node* _avl_subtree_leftmost_node(struct avl_node* n);
struct avl_node* _avl_subtree_remove(struct avl_node* n, int key);
struct avl_node* _avl_node_create(int key);

// three function that you will be modified in this recitation
struct avl_node* rightRotate(struct avl_node *y);
struct avl_node* leftRotate(struct avl_node *x);
struct avl_node* _avl_subtree_insert(struct avl_node* node, int key);

#endif
