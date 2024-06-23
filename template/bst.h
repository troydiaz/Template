/*
 * This file contains the definition of the interface for the binary search
 * tree you'll implement.  You should not modify anything in this file.  You
 * can find descriptions of the binary search tree functions, including their
 * parameters and their return values, in bst.c.
 */

#ifndef __BST_H
#define __BST_H

/*
 * Structure used to represent a binary search tree.
 */
struct bst;

/*
 * Basic binary search tree interface function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
/********************************************************************* 
** Function: bst_create
** Description: Allocate and initialize a new, empty BST and return a pointer to it.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Return bst pointer.
*********************************************************************/
struct bst* bst_create();

/********************************************************************* 
** Function: bst_free
** Description: Recursively free nodes in a given BST. Frees BST itself.
** Parameters: struct bst* bst
** Pre-Conditions: Pointer to bst.
** Post-Conditions: BST nodes are properly freed and BST struct is freed.
*********************************************************************/
void bst_free(struct bst* bst);

/********************************************************************* 
** Function: bst_size
** Description: Returns the number of elements in a given BST.
** Parameters: struct bst* bst
** Pre-Conditions: Pointer to bst
** Post-Conditions: Returns the size of the BST
*********************************************************************/
int bst_size(struct bst* bst);

/********************************************************************* 
** Function: bst_insert
** Description: Allocates memory and inserts a node into a BST given a key/value pair.
** Parameters: struct bst* bst, int key, void* value
** Pre-Conditions: Pointer to bst, key value, pointer to value
** Post-Conditions: Inserts a node in the proper spot of a BST
*********************************************************************/
void bst_insert(struct bst* bst, int key, void* value);

/********************************************************************* 
** Function: bst_remove
** Description: Removes a node given the node to remove, parent of that node, and the
key of the node to remove. Uses 5 cases, if bst is empty, if node to remove is a leaf node,
has two children, or has one child, and if the current node isn't the node to be removed.
** Parameters: struct bst* bst, int key
** Pre-Conditions: Pass in bst_node* for node to remove, the parent of that node, and the 
key of the node to remove.
** Post-Conditions: Removes a node and avoids restructuring the BST.
*********************************************************************/
void bst_remove(struct bst* bst, int key);

/********************************************************************* 
** Function: bst_get
** Description: Returns the value of a node given the BST and key.
** Parameters: struct bst* bst, int key
** Pre-Conditions: Pointer to bst and value of key
** Post-Conditions: Value of node is returned
*********************************************************************/
void* bst_get(struct bst* bst, int key);

/*
 * Binary search tree "puzzle" function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
/********************************************************************* 
** Function: bst_height
** Description: Returns the height of a given BST. 
** Parameters: struct bst* bst
** Pre-Conditions: Pointer to bst
** Post-Conditions: Returns max height of bst.
*********************************************************************/
int bst_height(struct bst* bst);

/********************************************************************* 
** Function: bst_path_sum
** Description: Validates if a given number is a path sum in a BST.
** Parameters: struct bst* bst, int sum
** Pre-Conditions: Pointer to bst and the sum to be checked
** Post-Conditions: Returns true or false
*********************************************************************/
int bst_path_sum(struct bst* bst, int sum);

/********************************************************************* 
** Function: bst_range_sum
** Description: Computes the sum of all keys in a BST between a lower/upper bound.
** Parameters: struct bst* bst, int lower, int upper
** Pre-Conditions: Pointer to bst and lower/upper bound limits (inclusive)
** Post-Conditions: Returns the value of a given range from BST
*********************************************************************/
int bst_range_sum(struct bst* bst, int lower, int upper);

/*
 * Structure used to represent a binary search tree iterator.
 */
struct bst_iterator;

/*
 * Binary search tree iterator interface prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst);
void bst_iterator_free(struct bst_iterator* iter);
int bst_iterator_has_next(struct bst_iterator* iter);
int bst_iterator_next(struct bst_iterator* iter, void** value);

#endif
