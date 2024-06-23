/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Troy Diaz
 * Email: diaztr@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* dynarray; // Pointer to dynarray struct
	struct dynarray* free_pq_elems; // Pointer to pq elems to free later
};

struct pq_element{
	void* value;
	int priority; // Priority position of element
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	// Allocate memory to pq
	struct pq* pq = malloc(sizeof(struct pq));

	// Pq holds dynarray elements
	pq->dynarray = dynarray_create();

	// Pq to hold all elements
	pq->free_pq_elems = dynarray_create();

	// If allocation fails
	if (pq->dynarray == NULL || pq->free_pq_elems == NULL){
		free(pq->dynarray);
		free(pq->free_pq_elems);
		return NULL;
	}

	// Return pointer to pq
	return pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue. That is the responsibility of the caller. However, you
 * do need to free the memory that holds each element stored in the priority 
 * queue. 
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	
	// Free all pq elements
	for (int i = 0; i < dynarray_size(pq->free_pq_elems); i++){
		free(dynarray_get(pq->free_pq_elems, i));
	}

	// Free dynarray and pq elems arrays
	dynarray_free(pq->dynarray);
	dynarray_free(pq->free_pq_elems);

	// Then free pq
	free(pq);

	return;
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	
	return isdynarray_empty(pq->dynarray);
}

void percolateUp(struct pq* pq, struct pq_element* pq_elem){
	
	// Find element that was last inserted
	int child = (dynarray_size(pq->dynarray) - 1);

	struct pq_element* temp;

	// Heapify, do while loop as long as child's index is greater than 0
  	while (child > 0){
		// Find parent node's position of newly added value
		int parent = ((child - 1)/2);

		// Store parent value into temp variable
		temp = dynarray_get(pq->dynarray, parent);

		// Percolate up if child's priority is less than parent node
		if (temp->priority > pq_elem->priority){

			// Make swap, move parent down, move child up
			dynarray_set(pq->dynarray, parent, pq_elem); 
			dynarray_set(pq->dynarray, child, temp); 
			
			// Update child index
			child = parent; 
		}
		else{ // If parent node's priority is greater than child then we can stop
			break;
		}
  	}
}

void pq_free_elem_later(struct pq* pq, struct pq_element* pq_elem){

	// Insert pq elems into list that'll be freed later
	dynarray_insert(pq->free_pq_elems, pq_elem);

	return;
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	
	// Allocate memory to pq_elem
	struct pq_element* pq_elem = malloc(sizeof(struct pq_element));

	// Store value and priority into pq elem
    pq_elem->value = value;
    pq_elem->priority = priority;
	
	// Pass in pq_elem
	dynarray_insert(pq->dynarray, pq_elem);
	
	percolateUp(pq, pq_elem);

	// To free later
	pq_free_elem_later(pq, pq_elem);

	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {

	// If dynamic array is empty
	if (dynarray_size(pq->dynarray) == 0){
		return NULL;
	}

	// Get data from first element in array
	struct pq_element* root = dynarray_get(pq->dynarray, 0);

	// First element of array has lowest priority, return value
	return root->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	
	// If dynamic array is empty
	if (dynarray_size(pq->dynarray) == 0){
		return 0;
	}

	struct pq_element* root = dynarray_get(pq->dynarray, 0);

	return root->priority;
}

void percolateDown(struct pq* pq, struct pq_element* replacement, int size, int index){

	while(1){
		// Indices of node's children
		int lchild = 2*index+1;
		int rchild = 2*index+2;

		// If indices are out of bounds and if left child exists
		if (lchild >= size){
			break;
		}

		// Get pq elem of left child
		struct pq_element* left_elem = dynarray_get(pq->dynarray, lchild);

		// Create pq elem for smaller priority of both children
		struct pq_element* smallest_elem = replacement;
		
		// Store idx of smallest_elem
		int smallest_elem_idx = index;

		// Compare left and inserted values priority
		if (left_elem->priority < smallest_elem->priority){
			smallest_elem = left_elem;
			smallest_elem_idx = lchild;
		}
		
		// If right child exists
		if (rchild < size) {

			// Get pq elem of right child
            struct pq_element* right_elem = dynarray_get(pq->dynarray, rchild);

			// Compare right and inserted values priority
            if (right_elem->priority < smallest_elem->priority){
                smallest_elem = right_elem;
                smallest_elem_idx = rchild;
            }
        }

		// Confirm that the value to be swapped has a lower priority before swapping
		if (replacement->priority == smallest_elem->priority){

			// Break if smallest elem has a greater priority
			break;
		}

		// Swap and update index to swapped index
		dynarray_set(pq->dynarray, index, smallest_elem);
		index = smallest_elem_idx;
	}

	// After percolating down and breaking at an equal priority, update inserted value's position
	dynarray_set(pq->dynarray, index, replacement);

	return;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	
	// If dynamic array is empty
	if (dynarray_size(pq->dynarray) == 0){
		return NULL;
	}

	// Store element with lowest priority to be removed
	struct pq_element* removed_elem = dynarray_get(pq->dynarray, 0);

	// If there's only one element in the pq
	if (dynarray_size(pq->dynarray) == 1){
		dynarray_remove(pq->dynarray, 0);
		return removed_elem->value;
	}

	// Find element that was last inserted
	int last_idx = (dynarray_size(pq->dynarray) - 1);

	// Store element used to replace removed element
	struct pq_element* replacement = dynarray_get(pq->dynarray, last_idx);

	// Set root node to be replaced by last inserted element
	dynarray_set(pq->dynarray, 0, replacement);

	// Remove element
	dynarray_remove(pq->dynarray, last_idx);

	int size = dynarray_size(pq->dynarray);
	int index = 0;

	// Percolate down function here;
	percolateDown(pq, replacement, size, index);

	// Return removed value
	return removed_elem->value;
}
