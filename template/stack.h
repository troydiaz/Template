/*
 * This file contains the definition of the interface for the stack you'll
 * implement.  You can find descriptions of the stack functions, including
 * their parameters and their return values, in stack.c.  You should not
 * modify anything in this file.
 */

#ifndef __STACK_H
#define __STACK_H

/*
 * Structure used to represent a stack.
 */
struct stack;

/*
 * Stack interface function prototypes.  Refer to stack.c for documentation
 * about each of these functions.
 */

/********************************************************************* 
** Function: stack_create
** Description: Allocates and initializes an empty stack and returns a pointer to it.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns pointer to new stack
*********************************************************************/
struct stack* stack_create();

/********************************************************************* 
** Function: stack_free
** Description: Frees memory within stack
** Parameters: struct stack* stack
** Pre-Conditions: Stack is not NULL
** Post-Conditions: Stack is freed
*********************************************************************/
void stack_free(struct stack* stack);

/********************************************************************* 
** Function: stack_isempty
** Description: Returns 1 if stack is empty, else if not empty then 0.
** Parameters: struct stack* stack
** Pre-Conditions: Stack is allocated
** Post-Conditions: If stack has or does not have elements, return value
*********************************************************************/
int stack_isempty(struct stack* stack);

/********************************************************************* 
** Function: stack_push
** Description: Adds a value onto top of stack
** Parameters: struct stack* stack, void* val
** Pre-Conditions: Stack is not NULL
** Post-Conditions: New value pushed onto top of stack
*********************************************************************/
void stack_push(struct stack* stack, void* val);

/********************************************************************* 
** Function: stack_top
** Description: Returns value at the front or top of stack
** Parameters: struct stack* stack
** Pre-Conditions: Stack is not NULL
** Post-Conditions: Returns top value of stack
*********************************************************************/
void* stack_top(struct stack* stack);

/********************************************************************* 
** Function: stack_pop
** Description: Removes top value of stack
** Parameters: struct stack* stack
** Pre-Conditions: Stack is not NULL or empty
** Post-Conditions: Removes top value of stack
*********************************************************************/
void* stack_pop(struct stack* stack);

/********************************************************************* 
** Function: get_stack_size
** Description: Returns stack size
** Parameters: struct stack* stack
** Pre-Conditions: Stack is not NULL or empty
** Post-Conditions: Returns size of stack
*********************************************************************/
void* get_stack_size(struct stack* stack);

#endif
