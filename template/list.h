/*
 * This file contains the definition of the interface for the linked list
 * you'll implement.  You can find descriptions of the linked list functions,
 * including their parameters and their return values, in list.c. You should
 * not modify anything in this file.
 */

#ifndef __LIST_H
#define __LIST_H

/*
 * Structure used to represent a singly-linked list.
 */
struct node;
struct list;

/*
 * Linked list interface function prototypes.  Refer to list.c for
 * documentation about each of these functions.
 */

/********************************************************************* 
** Function: list_create
** Description: Allocate memory to linked list.
** Parameters: None
** Pre-Conditions: none
** Post-Conditions: Returns a pointer to empty linked list.
*********************************************************************/
struct list* list_create();

/********************************************************************* 
** Function: list_free
** Description: Freeining memory from linked list.
** Parameters: 
**    list - linked list
** Pre-Conditions: pointer to linked list
** Post-Conditions: Frees memory of nodes then frees the list itself.
*********************************************************************/
void list_free(struct list* list);

/********************************************************************* 
** Function: list_insert
** Description: Inserts a new node at start of list.
** Parameters: 
**    list - linked list, val - value new node stores
** Pre-Conditions: pointer to list and value of val
** Post-Conditions: Inserts a new node with value at the head of list.
*********************************************************************/
void list_insert(struct list* list, void* val);

/********************************************************************* 
** Function: list_insert_end
** Description: Inserts a new node at end of list.
** Parameters: 
**    list - linked list, val - value new node stores
** Pre-Conditions: pointer to list and value of val
** Post-Conditions: Inserts a new node with value at end of list.
*********************************************************************/
void list_insert_end(struct list* list, void* val);

/********************************************************************* 
** Function: list_remove
** Description: Removes node at specified value.
** Parameters: 
**    list - linked list, val - value node stores, cmp - the function to compare 
value to be removed and value in linked list
** Pre-Conditions: pointer to list, value of val, cmp function which returns 
if value is equiv to value in linked list
** Post-Conditions: Removes node at spec value and frees the memory.
*********************************************************************/
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));

/********************************************************************* 
** Function: list_remove_end
** Description: Removes last node.
** Parameters: 
**    list - linked list
** Pre-Conditions: pointer to list
** Post-Conditions: Removes the very last node and frees the memory of that node.
*********************************************************************/
void list_remove_end(struct list* list);

/********************************************************************* 
** Function: list_position
** Description: Gets value of linked list given the value.
** Parameters: 
**    list - linked list, val - value in linked list, cmp the function to compare 
value to be found and value in linked list
** Pre-Conditions: pointer to list, value of val, cmp function which returns 
if value is equiv to value in linked list
** Post-Conditions: Returns position of value in linked list.
*********************************************************************/
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));

/********************************************************************* 
** Function: list_reverse
** Description: Reverses the linked list values and pointers.
** Parameters: 
**    list - linked list
** Pre-Conditions: pointer to list
** Post-Conditions: Reverses the list order.
*********************************************************************/
void list_reverse(struct list* list);

#endif
