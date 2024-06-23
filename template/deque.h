/*
 * This file contains the definition of the interface for the deque you'll
 * implement.  You can find descriptions of the deque functions, including
 * their parameters and their return values, in deque.c.  You should not
 * modify anything in this file.
 */

#ifndef __DEQUE_H
#define __DEQUE_H

/*
 * Structure used to represent a deque.
 */
struct deque;

/*
 * Deque interface function prototypes.  Refer to deque.c for documentation
 * about each of these functions.
 */
struct deque* deque_create();
void deque_free(struct deque* deque);
int deque_isempty(struct deque* deque);
void deque_add_to_front(struct deque* deque, void* val);
void deque_add_to_back(struct deque* deque, void* val);
void* deque_front(struct deque* deque);
void* deque_back(struct deque* deque);
void* deque_remove_front(struct deque* deque);
void* deque_remove_back(struct deque* deque);
void deque_display(struct deque* deque, void (*p)(void* a));

#endif
