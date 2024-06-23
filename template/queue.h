/*
 * This file contains the definition of the interface for the queue you'll
 * implement.  You can find descriptions of the queue functions, including
 * their parameters and their return values, in queue.c.  You should not
 * modify anything in this file.
 */

#ifndef __QUEUE_H
#define __QUEUE_H

/*
 * Structure used to represent a queue.
 */
struct queue;

/*
 * Queue interface function prototypes.  Refer to queue.c for documentation
 * about each of these functions.
 */
/********************************************************************* 
** Function: queue_create
** Description: Allocates memory to queue using dynamic array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns pointer to queue
*********************************************************************/
struct queue* queue_create();

/********************************************************************* 
** Function: queue_free
** Description: Frees memory of queue
** Parameters: struct queue* queue
** Pre-Conditions: none
** Post-Conditions: Frees data of queue, then queue itself
*********************************************************************/
void queue_free(struct queue* queue);

/********************************************************************* 
** Function: queue_isempty
** Description: Returns 1 if queue is empty, 0 otherwise
** Parameters: struct queue* queue
** Pre-Conditions: Queue is not NULL 
** Post-Conditions: Returns value if queue is empty or not
*********************************************************************/
int queue_isempty(struct queue* queue);

/********************************************************************* 
** Function: queue_enqueue
** Description: Adds value to queue
** Parameters: struct queue* queue, void* val
** Pre-Conditions: Queue is not NULL
** Post-Conditions: Inserts value into queue
*********************************************************************/
void queue_enqueue(struct queue* queue, void* val);

/********************************************************************* 
** Function: queue_front
** Description: Returns value stored at front of queue
** Parameters: struct queue* queue
** Pre-Conditions: Queue is not empty
** Post-Conditions: Gets value fo queue at the start of array
*********************************************************************/
void* queue_front(struct queue* queue);

/********************************************************************* 
** Function: queue_dequeue
** Description: Removes value in queue
** Parameters: struct queue* queue
** Pre-Conditions: Queue is not NULL or empty
** Post-Conditions: Removes value of queue at index 0
*********************************************************************/
void* queue_dequeue(struct queue* queue);

/********************************************************************* 
** Function: get_queue_size
** Description: Returns queue size
** Parameters: struct queue* queue
** Pre-Conditions: Queue is not NULL or empty
** Post-Conditions: Returns queue size
*********************************************************************/
void* get_queue_size(struct queue* queue);

/*
 * helper function for testing
 */
void queue_print(struct queue* queue, void (*p) (void* a));


#endif
