/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Troy Diaz
 * Email: diaztr@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {

  // Allocate memory to binary search tree
  struct bst* bst = malloc(sizeof(struct bst));

  // If allocation fails
  if (bst == NULL){
    return NULL;
  }

  // Set root to be NULL
  bst->root = NULL;
  
  // Return pointer to bst
  return bst;
}

void bst_free_node(struct bst_node* node){

  // If the children of node is NULL, then return back to previous call on stack
  if (node == NULL){
    return;
  }

  // Pass in left node until we reach a leaf node
  bst_free_node(node->left);

  // Pass in right node until we reach a leaf node
  bst_free_node(node->right);

  // Free leaf node 
  free(node);
  
  return;
}
/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {

  // If bst is empty
  if (bst->root == NULL){
    return;
  }

  // Pass in root node
  bst_free_node(bst->root);

  // Set root node to be NULL
  bst->root = NULL;

  // Free bst itself
  free(bst);

  return;
}

int bst_node_count(struct bst_node* node){
  if (node == NULL){
    return 0;
  }

  /*
  1) Add root node
  2) Get size of left subtree
  3) Get size of right subtree
  */
  return bst_node_count(node->left) + 1 + bst_node_count(node->right);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {

  // If bst is empty
  if (bst->root == NULL){
    return 0;
  }

  // Pass in root node
  return bst_node_count(bst->root);
}

void insert_node(struct bst_node* node, int key, void* value){

  if (node == NULL){
    return;
  }

  // If the value is less than the node's value, add to left subtree
  if (key < node->key){
    // If left node is empty, add a new left node 
    if (node->left == NULL){
      // Allocate memory to left node
      node->left = malloc(sizeof(struct bst_node));
      if (node->left == NULL){
        return;
      }
      // Initialize left node
      node->left->key = key;
      node->left->value = value;
      node->left->left = NULL;
      node->left->right = NULL;
    }
    else{

      // If left node has children, recusively call this function and compare the key to its node(s) 
      insert_node(node->left, key, value);
    }
  }
  // Repeat process with right subtree, if value is greater than the node's value
  else{
    if (node->right == NULL){
      node->right = malloc(sizeof(struct bst_node));
      if (node->right == NULL){
        return;
      }
      node->right->key = key;
      node->right->value = value;
      node->right->right = NULL;
      node->right->left = NULL;
    }
    else{
      insert_node(node->right, key, value);
    }  
  }
  return;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {

  // If bst is empty then insert node at root
  if (bst->root == NULL){
    // Allocate memory to new node
    struct bst_node* new_node = malloc(sizeof(struct bst_node));
    
    // Initialize new_node
    new_node->value = value;
    new_node->key = key;

    // Set children to be NULL
    new_node->left = NULL;
    new_node->right = NULL;

    // Assign values to root node
    bst->root = new_node;
  }
  else{
    // Find available spot for new node starting at root node
    insert_node(bst->root, key, value);
  }

  return;
}

struct bst_node* get_parent_node(struct bst_node* node, int key){

  // Set parent to be NULL initially
  struct bst_node* parent = NULL; 

  // Traverse nodes
  while (node != NULL) {

    // Check if node has the key, then return parent node
    if (node->key == key)
      return parent;

    // Set node to be parent and set node to be left node
    else if (node->key > key){
      parent = node;
      node = node->left; 
    }

    // Do the same with right node if key is greater
    else  {
      parent = node;
      node = node->right;
    }

  }
  // The node with key does not exist 
  if (node == NULL)
    return NULL; 
}

void* bst_remove_node(struct bst_node* node, struct bst_node* parent, int key){
  /*
  If the current node has the key, then
    1) Case: 1, bst is empty
    2) Case: 2, node found is a leaf node
    3) Case: 3, node found has two child nodes
    4) Case: 4, node found has either left or right child node

  If the current node doesn't have key, then
    5) Recursively call function to move through left and right subtrees
  */

  // 1) If bst is empty
  if (node == NULL){
    return;
  }

  // If current node has the key we're looking for
  if(key == node->key){

    // 2) If key is a leaf node, free node
    if (node->left == NULL && node->right == NULL){
      
      // Update parent's left node if equal to current node
      if (parent->left == node){
        parent->left = NULL;
      }

      // Do the same if right node
      else if (parent->right == node){
        parent->right = NULL;
      }
      
      // Finally free leaf node
      free(node);
    }

    // 3) If key contains two children, update node to point to in-order successor
    else if (node->left != NULL && node->right != NULL){
      
      // Assign temp node to find in order successor
      struct bst_node* temp = node->right;
      
      // Assign temp parent to track parent of in order successor
      struct bst_node* temp_parent = node;

      // Traverse to find least greatest node
      while (temp->left != NULL){
        temp_parent = temp;
        temp = temp->left;
      }
      
      // Replace node's data with in order successor's data 
      node->value = temp->value;
      node->key = temp->key;

      // Free successor node, go through all cases again
      bst_remove_node(temp, temp_parent, temp->key); 
    }

    // 4) If key contains a single child, check left and right node
    else if(node->left != NULL){

      // Update child node to point to node's parent
      struct bst_node* child;
      child = node->left;

      if (parent != NULL) {
        
        // If node is current parent's left node, assign child left node to the parent
        if (parent->left == node){
          parent->left = child;
        } 
    
        // Else, assign right child node to the parent
        else{
          parent->right = child;
        }

        // After reassigning parent's child node, free current node
        free(node);
      }
    }
    
    // Do same with right node
    else if(node->right != NULL){
      
      struct bst_node* child;
      child = node->right;

      if (parent != NULL) {

        if (parent->left == node){
          parent->left = child;
        }

        else{
          parent->right = child;
        }

        free(node);
      }
    }
  }
  
  // 5) If key is less than node's key, check left subtree
  else if (key < node->key){
    if (node->left != NULL){
      bst_remove_node(node->left, parent, key);
    }
  }

  // Check right subtree
  else if (key > node->key){
    if (node->right != NULL){
      bst_remove_node(node->right, parent, key);
    }
  }

  return;
}

struct bst_node* bst_get_node(struct bst_node* node, int key){

  // If key has not been found
  if (node == NULL){
    return NULL;
  }

  // If key is equal to the nodes key, return node
  if (key == node->key){
    // Returning pointer to node
    return node;
  }
  // If key is less than nodes key, move to left subtree
  if (key < node->key){
    return bst_get_node(node->left, key);
  }
  // Move to right subtree
  else{
    return bst_get_node(node->right, key);
  }
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  
  // If bst empty
  if (bst->root == NULL){
    return;
  }

  // Find node to remove by comparing node and its key
  struct bst_node* node_to_remove = bst_get_node(bst->root, key);

  // Get parent of node with key
  struct bst_node* parent = get_parent_node(bst->root, key);

  // If the node to remove does not exist, return 
  if (node_to_remove == NULL){
    return;
  }

  // Pass in the node with key, the parent, and key
  bst_remove_node(node_to_remove, parent, key);
  
  return;
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {

  // If bst empty
  if (bst->root == NULL){
    return NULL;
  }

  // Get nodes value by comparing node and key
  struct bst_node* temp = bst_get_node(bst->root, key);
  
  // If key not found
  if (temp == NULL){
    return NULL;
  }

  // Return the value of bst node
  return temp->value;
}



/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

void* bst_height_node(struct bst_node* node){

  // If bst is empty
  if (node == NULL){
      return -1;
  }
  
  // If root has no children
  if (node->left == NULL && node->right == NULL){
    return 0;
  }

  // Store size of left and right subtree
  int leftmaxdepth = bst_height_node(node->left);
  int rightmaxdepth = bst_height_node(node->right);

  // If left subtree is greater than right, return left subtree size + root
  if (leftmaxdepth > rightmaxdepth){
    return 1 + leftmaxdepth;
  }
  // Return right subtree size + root
  else{
    return 1 + rightmaxdepth;
  }
}

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
    // Also same as max depth
    return bst_height_node(bst->root);
 }

int bst_path_sum_node(struct bst_node* node, int sum, int counter){
  
  // If bst empty
  if (node == NULL){
    return 0;
  }

  // Add nodes value to counter
  counter += node->key;

  // If we reached a leaf node and the counter is equal to the path sum, then return true
  if (node->left == NULL && node->right == NULL && counter == sum){
    return 1;
  }
  // Else, recursively search left and right subtree
  else{
    return bst_path_sum_node(node->left, sum, counter) || bst_path_sum_node(node->right, sum, counter);
  }
}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {

  // if bst empty
  if (bst->root == NULL){
    return 0;
  }

  // To keep track of sums, initially by starting at 0
  int counter = 0;

  // First check, if root is the sum, then return false bc it's not a valid path sum
  if (counter == sum){
    return 0;
  }
  else{
    // Start at root, pass in sum to find, and counter with value of root node
    return bst_path_sum_node(bst->root, sum, counter);
  }

}

int bst_range_sum_node(struct bst_node* node, int lower, int upper){
  
  // If bst empty
  if (node == NULL){
    return 0;
  }

  // If node's value is greater than upper bound, explore left subtree, look for smaller values
  if (node->key > upper){
    return bst_range_sum_node(node->left, lower, upper);
  }
  
  // If node's value is less than lower bound, explore right subtree, look for larger values
  if (node->key < lower){
    return bst_range_sum_node(node->right, lower, upper);
  }

  // If value is within range, add key and recursively look in left and right nodes
  return node->key + bst_range_sum_node(node->left, lower, upper) + bst_range_sum_node(node->right, lower, upper);

} 

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  
  // if bst empty
  if (bst->root == NULL){
    return 0;
  }

  // Return range sum
  return bst_range_sum_node(bst->root, lower, upper);
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  /*
   * FIXME:
   */
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  /*
   * FIXME:
   */
  if (value) {
    *value = NULL;
  }
  return 0;
}
