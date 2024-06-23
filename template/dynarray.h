/*
 * This file contains the definition of the interface for the dynamic array
 * you'll implement.  You can find descriptions of the dynamic array functions,
 * including their parameters and their return values, in dynarray.c. You
 * should not modify anything in this file.
 */

#ifndef __DYNARRAY_H
#define __DYNARRAY_H

/*
 * Structure used to represent a dynamic array.
 */
struct dynarray;

/*
 * Dynamic array interface function prototypes.  Refer to dynarray.c for
 * documentation about each of these functions.
 */

/********************************************************************* 
** Function: dynarray_create
** Description: Allocate memory to dynamic array.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Created array is empty and has a capacity of 2.
*********************************************************************/
struct dynarray* dynarray_create();

/********************************************************************* 
** Function: dynarray_free
** Description: Free memory of dynamic array.
** Parameters: 
**    da - dynamic array
** Pre-Conditions: the memory of da, the dynamic array
** Post-Conditions: Dynamic array elements are freed, then the dynamic array
itself is freed.
*********************************************************************/
void dynarray_free(struct dynarray* da);

/********************************************************************* 
** Function: dynarray_size
** Description: Returns the size of dynamic array.
** Parameters: 
**    da - dynamic array
** Pre-Conditions: the memory of da
** Post-Conditions: Returns the size or number of elements in da.
*********************************************************************/
int dynarray_size(struct dynarray* da);

/********************************************************************* 
** Function: dynarray_insert
** Description: Inserts element at end of dynamic array.
** Parameters: 
**    da - dynamic array, val - the value to be inserted
** Pre-Conditions: the memory of da, and value of val
** Post-Conditions: Increments dynamic array size by one and last element
is now val.
*********************************************************************/
void dynarray_insert(struct dynarray* da, void* val);

/********************************************************************* 
** Function: dynarray_remove
** Description: Removes element at specified value.
** Parameters: 
**    da - dynamic array, idx - index at to remove value in dynamic array 
** Pre-Conditions: the memory of da, and the value of idx index
** Post-Conditions: Decrements dynamic size by one and specified value
is removed from dynamic array.
*********************************************************************/
void dynarray_remove(struct dynarray* da, int idx);

/********************************************************************* 
** Function: dynarray_get
** Description: Gets the value of dynamic array at specified index.
** Parameters: 
**    da - dynamic array, idx - index at to find element in dynamic array
** Pre-Conditions: the memory of da, the value of idx index
** Post-Conditions: Returns value of element at index idx in dynamic array.
*********************************************************************/
void* dynarray_get(struct dynarray* da, int idx);

/********************************************************************* 
** Function: dynarray_set
** Description: sets the value of dynamic array at specified index
** Parameters: 
**    da - dynamic array, idx - index, val - value to insert
** Pre-Conditions: the memory of da, the value of idx index, the value of val
** Post-Conditions: Updates element at specified index to val.
*********************************************************************/
void dynarray_set(struct dynarray* da, int idx, void* val);

#endif
