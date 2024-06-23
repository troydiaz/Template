/*
 * This file contains the definition of the interface for the priority queue
 * you'll implement.  You can find descriptions of the priority queue functions,
 * including their parameters and their return values, in pq.c.
 *
 * You should not modify this file.
 */

#ifndef __PQ_H
#define __PQ_H

/*
 * Structure used to represent a priority queue.
 */
struct pq;

/*
 * Priority queue interface function prototypes.  Refer to pq.c for
 * documentation about each of these functions.
 */

/********************************************************************* 
** Function: pq_create
** Description: allocate and initialize an empty priority queue
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: returns a pointer to empty priority queue
*********************************************************************/
struct pq* pq_create();

/********************************************************************* 
** Function: pq_free
** Description: frees the memory allocated to a given priority queue
** Parameters: pq - priority queue
** Pre-Conditions: none
** Post-Conditions: pq destroyed
*********************************************************************/
void pq_free(struct pq* pq);

/********************************************************************* 
** Function: pq_isempty
** Description: function should return 1 if the specified priority queue is empty 
and 0 otherwise
** Parameters: pq - priority queue
** Pre-Conditions: none 
** Post-Conditions: returns if pq is empty or not
*********************************************************************/
int pq_isempty(struct pq* pq);

/********************************************************************* 
** Function: pq_insert
** Description: function should insert a given element into a priority queue with a
specified priority value
** Parameters: pq - priority queue, value - value to be inserted, priority - the
priority value to be assigned to newly inserted element
** Pre-Conditions: none
** Post-Conditions: inserts value into pq
*********************************************************************/
void pq_insert(struct pq* pq, void* value, int priority);

/********************************************************************* 
** Function: pq_first
** Description: return the value of the first item in a priority
** Parameters: pq - priority queue
** Pre-Conditions: none
** Post-Conditions: returns value
*********************************************************************/
void* pq_first(struct pq* pq);

/********************************************************************* 
** Function: pq_first_priority
** Description: return the priority of the first item in a priority queue
** Parameters: pq - priority queue
** Pre-Conditions: none
** Post-Conditions: returns priority 
*********************************************************************/
int pq_first_priority(struct pq* pq);

/********************************************************************* 
** Function: pq_remove_first
** Description: return the value of the first item in a priority and remove that item
from the queue
** Parameters: pq - priority queue
** Pre-Conditions: none
** Post-Conditions: removes and returns the value of the element with the lowest
priority value
*********************************************************************/
void* pq_remove_first(struct pq* pq);

#endif
