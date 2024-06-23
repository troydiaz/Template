/*********************************************************************** 
** Program Filename: stack
** Author: Troy Diaz
** Date: 04/28/2024
** Description: Building an ADT - stack, using a linked list. Basic operations 
include allocating memory to stack structure, freeing memory help in stack, returning
empty if stack is empty, push new value on top of stack, and pop value from stack. 
O(1) average runtime complexity.
** Input: none
** Output: none
*********************************************************************/

/*
 * This file is where you should implement your stack.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name: Troy Diaz
 * Email: diaztr@oregonstate.edu
 */

#include <stdlib.h>

#include "stack.h"
#include "list.h"

/*
 * This is the structure that will be used to represent a stack.  This
 * structure specifically contains a single field representing a linked list
 * that should be used as the underlying data storage for the stack.
 *
 * You should not modify this structure.
 */
struct stack {
  struct list* list;
};

/*
 * This function should allocate and initialize a new, empty stack and return
 * a pointer to it.
 */
struct stack* stack_create() {
	
	// Allocate memory to stack 
	struct stack* stack = malloc(sizeof(struct stack));

	// Create stack with linked list
	stack->list = list_create();

	// If memory allocation fails
	if (stack == NULL){
		free(stack);
		return NULL;
	}

	// Return pointer to stack
	return stack;
}

/*
 * This function should free the memory associated with a stack.  While this
 * function should up all memory used in the stack itself, it should not free
 * any memory allocated to the pointer values stored in the stack.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack) {
	
	// If stack is already freed or empty
	if (stack == NULL){
		return;
	}

	// Free linked list in stack
	list_free(stack->list);

	// Free stack itself
	free(stack);

	return;
}

/*
 * This function should indicate whether a given stack is currently empty.
 * Specifically, it should return 1 if the specified stack is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(struct stack* stack) {
	
	// If stack is not empty
	if (!list_empty(stack->list)){
		return 0;
	}

	return 1;
}

/*
 * This function should push a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(struct stack* stack, void* val) {

	// Return if stack is unitialized
	if (stack == NULL){
		return;
	}

	// Push value onto stack
	list_insert(stack->list, val);

	return;
}

/*
 * This function should return the value stored at the top of a given stack
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   stack - the stack from which to query the top value.  May not be NULL.
 */
void* stack_top(struct stack* stack) {

	// If list is empty
	if (list_empty(stack->list)){
		return NULL;
	}

	// Returning top value at stack
	return list_front(stack->list);
}

/*
 * This function should pop a value from a given stack and return the popped
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was popped.
 */
void* stack_pop(struct stack* stack) {
	
	// If stack is unitialized or empty
	if (stack == NULL || list_empty(stack->list)){
		return NULL;
	}

	// Get value from top
	void* pop_value = list_front(stack->list);
	
	// Pop value from stack
	list_remove_front(stack->list);

	// Return popped value
	return pop_value;
}

// Helper Functions

void* get_stack_size(struct stack* stack){

	// If stack is unitialized or empty
	if (stack == NULL || list_empty(stack->list)){
		return NULL;
	}

	// Returning size of stack
	return get_list_size(stack->list);
}