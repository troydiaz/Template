/*
 * This file contains the definition of the interface for the hash table
 * you'll implement.  You can find descriptions of the hash table functions,
 * including their parameters and their return values, in hash_table.c.
 *
 * You should not modify this file.
 */

#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H 

/*
 * Structure used to represent a hash table.
 */
struct ht;

/*
 * Hash table interface function prototypes.  Refer to hash_table.c for
 * documentation about each of these functions.
 */

/*********************************************************************
** Function: ht_create
** Description: Create an empty hash table and return a pointer to it
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Pointer to ht
*********************************************************************/
struct ht* ht_create();

/*********************************************************************
** Function: ht_isempty
** Description: Checks if hash table is empty
** Parameters: struct ht* ht
** Pre-Conditions: none
** Post-Conditions: Returns 1 if hash table is empty, 0 if not
*********************************************************************/
int ht_isempty(struct ht* ht);

/*********************************************************************
** Function: ht_size
** Description: Returns the number of elements in a hash table, not capacity
** Parameters: struct ht* ht
** Pre-Conditions: none
** Post-Conditions: Return number of buckets with values, ht->elems
*********************************************************************/
int ht_size(struct ht* ht);

/*********************************************************************
** Function: ht_free
** Description: Frees mememory allocated to a given hash table
** Parameters: struct ht* ht
** Pre-Conditions: none
** Post-Conditions: Frees memory
*********************************************************************/
void ht_free(struct ht* ht);

/*********************************************************************
** Function: ht_hash_func
** Description: Takes a key and maps it to an integer index value in a hash table
and returns it
** Parameters: struct ht* ht, void* key, int (*convert)(void*)
** Pre-Conditions: none
** Post-Conditions: Returns index
*********************************************************************/
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*));

/*********************************************************************
** Function: ht_insert
** Description: Inserts an element into a hash table with a key.
** Parameters: struct ht* ht, void* key, void* value, int (*convert)(void*)
** Pre-Conditions: none
** Post-Conditions: New value is inserted into ht, size increments
*********************************************************************/
void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*));

/*********************************************************************
** Function: ht_lookup
** Description: Looks for a specified element in a hash table given the key
** Parameters: struct ht* ht, void* key, int (*convert)(void*)
** Pre-Conditions: none
** Post-Conditions: Returns value if found, if not, NULL
*********************************************************************/
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*));

/*********************************************************************
** Function: ht_remove
** Description: Removes a given element in a hash table with specificed key
** Parameters: struct ht* ht, void* key, int (*convert)(void*)
** Pre-Conditions: none
** Post-Conditions: Element is removed and freed, size decrements
*********************************************************************/
void ht_remove(struct ht* ht, void* key, int (*convert)(void*));

#endif
