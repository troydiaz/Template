/*
 * This file is where you should implement your deque.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name: Troy Diaz
 * Email: diaztr@oregonstate.edu
 */

#include <stdlib.h>

#include "deque.h"
#include "db_list.h"

/*
 * This is the structure that will be used to represent a deque.  This
 * structure specifically contains a single field representing a doubly linked list
 * that should be used as the underlying data storage for the deque.
 *
 * You should not modify this structure.
 */
struct deque {
  struct db_list* db_list;
};

/*
 * This function should allocate and initialize a new, empty deque and return
 * a pointer to it.
 */
struct deque* deque_create() {

	// Create deque pointer
	struct deque* deque = malloc(sizeof(deque));

	// Allocate mem to deque db list
	deque->db_list = db_list_create();

	// If allocation fails
	if (deque == NULL){
		free(deque);
		return NULL;
	}
	
	// Return pointer to deque
	return deque;
}

/*
 * This function should free the memory associated with a deque.  While this
 * function should up all memory used in the deque itself, it should not free
 * any memory allocated to the pointer values stored in the deque.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   deque - the deque to be destroyed.  May not be NULL.
 */
void deque_free(struct deque* deque) {

	// If deque is unitialized
	if (deque == NULL){
		return;
	}

	// Free db list
	db_list_free(deque->db_list);

	// Finally free deque
	free(deque);
	
	return;
}

/*
 * This function should indicate whether a given deque is currently empty.
 * Specifically, it should return 1 if the specified deque is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   deque - the deque whose emptiness is being questioned.  May not be NULL.
 */
int deque_isempty(struct deque* deque) {
	
	// Get size of db list, return 1 if it it empty
	if (db_list_empty(deque->db_list)){
		return 1;
	}

	return 0;
}

/*
 * This function should add a new value to the front of a given deque.  The value to be
 * inserted is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   deque - the deque onto which a value is to be inserted.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void deque_add_to_front(struct deque* deque, void* val) {

	// Add node to front
	db_list_insert(deque->db_list, val);

	return;
}

/*
 * This function should add a new value to the back of a given deque.  The value to be
 * inserted is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   deque - the deque onto which a value is to be inserted.  May not be NULL.
 *   val - the value to be inserted.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void deque_add_to_back(struct deque* deque, void* val) {
	
	// Add node to back
	db_list_insert_end(deque->db_list, val);
	
	return;
}

/*
 * This function should return the value stored at the front of a given deque
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   deque - the deque from which to query the front value.  May not be NULL.
 */
void* deque_front(struct deque* deque) {
	
	// Get front next node
	return db_list_front(deque->db_list);
}

/*
 * This function should return the value stored at the back of a given deque
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   deque - the deque from which to query the back value.  May not be NULL.
 */
void* deque_back(struct deque* deque) {

	// Get back previous node
	return db_list_back(deque->db_list);
}

/*
 * This function should remove a value at the front from a given deque and return the
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   deque - the deque from which a value is to be removed.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was removed.
 */
void* deque_remove_front(struct deque* deque) {

	// Store front next node
	struct deque* temp = deque_front(deque);

	// Remove that node
	db_list_remove_front(deque->db_list);

	// Return removed node
	return temp;
}

/*
 * This function should remove a value at the back from a given deque and return the
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   deque - the deque from which a value is to be removed.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was removed.
 */
void* deque_remove_back(struct deque* deque) {
	
	// Store back previous node
	struct deque* temp = deque_back(deque);

	// Remove that node
	db_list_remove_end(deque->db_list);

	// Return removed node
	return temp;
}

void print_deque(void* a){

	// Assign node to be an int pointer
	int* node = (int*)a;

	// Print out dereferenced nodes
	printf("%d\n", *node);
}

/*
 * This function should display/print all the elements of the given deque 
 * from beginning to the end. 
 *
 * This function will be passed a *function pointer* called `p` that you
 * should use to print each element.
 * 
 * Params:
 * deque - the deque from which to display. May not be NULL.
 * p - pointer to a function that can be passed one void* value from
 *     to print it out, as described above.
 */
void deque_display(struct deque* deque, void (*p)(void* a)){
	
	// Pass in db list and pointer to print_deque
	db_list_display_forward(deque->db_list, p);

	return;
}	
