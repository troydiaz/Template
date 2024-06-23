/*
 * In this file, you will write the structures and functions needed to
 * implement a hash table.  Feel free to implement any helper functions
 * you need in this file to implement a hash table.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Troy Diaz
 * Email: diaztr@oregonstate.edu
 */

#include <stdlib.h>
#include <string.h>

#include "dynarray.h"
#include "list.h"
#include "hash_table.h"


/*
 * This is the structure that represents a hash table.  You must define
 * this struct to contain the data needed to implement a hash table.
 */
struct ht{
    struct node** lists; // List of pointers
    int size; // Buckets of hash table
    int elems; // Elements stored in hash table, i.e. values in ht
};

struct node{
    void* key; // Identifier of node
    void* val; // Value stored in node
    struct node* next;
};

/*
 * This function should allocate and initialize an empty hash table and
 * return a pointer to it.
 */
struct ht* ht_create(){
    // Allocate memory
    struct ht* ht = malloc(sizeof(struct ht));

    // Start with 20 buckets (capacity), no values
    ht->size = 20;
    ht->elems = 0;

    // Create list of pointers
    ht->lists = (struct node**)malloc(ht->size * sizeof(struct node*));

    return ht;
}

/*
 * This function should free the memory allocated to a given hash table.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the hash table.  That is the responsibility of the caller.
 *
 * Params:
 *   ht - the hash table to be destroyed.  May not be NULL.
 */
void ht_free(struct ht* ht){
    
    struct node* node = NULL;
    struct node* next = NULL;

    // Free individual pointers to lists
    for(int i = 0; i < ht->size; i++){
        node = ht->lists[i];

        // Traverse list and free nodes
        while (node != NULL){
            next = node->next;
            free(node);
            node = next;
        }
    }

    // Free ht lists
    free(ht->lists);

    // Finally free ht
    free(ht);

    return;
}

/*
 * This function should return 1 if the specified hash table is empty and
 * 0 otherwise.
 *
 * Params:
 *   ht - the hash table whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if ht is empty and 0 otherwise.
 */
int ht_isempty(struct ht* ht){
    // If there are no values in the buckets, return 1
    if (ht->elems == 0){
        return 1;
    }
    else{
        return 0;
    }
}

/*
 * This function returns the size of a given hash table (i.e. the number of
 * elements stored in it, not the capacity).
 *
 * Params:
 *   ht - the hash table whose size is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return the size of the given hash table.
 */
int ht_size(struct ht* ht){
    // Return number of buckets with values 
    return ht->elems;
}

// Function to convert key to int
int convert(void* key){
    return *((int*)key);
}

// Function to get hash index
int hash(void* key, int size){
    int index = convert(key) % size;
    if (index < 0){
        index += size;
    }
    return index;
}

/*
 * This function takes a key, maps it to an integer index value in the hash table,
 * and returns it. The hash function is passed in as a function pointer, stored in 'convert'
 * Assuming the passed in hash function is well designed.
 *
 * Params:
 *   ht - the hash table into which to store the element.  May not be NULL.
 *   key - the key of the element used to calculate the index
 *   convert - a pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 *
 * Return:
 *   Should return the index value of 'key' in the hash table .
 */
int ht_hash_func(struct ht* ht, void* key, int (*convert)(void*)){

    // Create value to identify element
    int hash_code = convert(key); 

    // Index is within bounds of hash table
    int index = hash_code % ht_size(ht);

    // Reverse signs if negative
    if (index < 0){
        index += ht_size(ht);
    }

    return index;
}

// Function to update a node, given a key and a value
void set_node(struct node* node, void* key, void* value){
  
  node->key = key;
  node->val = value;
  node->next = NULL;

  return;
}

/*
 * This function should insert a given element into a hash table with a
 * specified key. Note that you cannot have two same keys in one hash table.
 * If the key already exists, update the value associated with the key.  
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * Resolution of collisions is requried, use either chaining or open addressing.
 * If using chaining, double the number of buckets when the load factor is >= 4
 * If using open addressing, double the array capacity when the load factor is >= 0.75
 * load factor = (number of elements) / (hash table capacity)
 *
 * Params:
 *   ht - the hash table into which to insert an element.  May not be NULL.
 *   key - the key of the element
 *   value - the value to be inserted into ht.
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */

void ht_insert(struct ht* ht, void* key, void* value, int (*convert)(void*)){
    
    // Get bucket index
    int bucket_index = hash(key, ht->size);

    // Update duplicate value and return
    struct node* curr = ht->lists[bucket_index];
    while(curr != NULL){
        // Compare values
        if(!strcmp(key, curr->key)){
            curr->val = value;
            // Exit function after updating
            return;
        }
        curr = curr->next;
    }
    
    // Allocate mem to new node, initialize key and value
    struct node* new_node = malloc(sizeof(struct node));
    set_node(new_node, key, value);

    // If bucket index is empty, insert new node
    if(ht->lists[bucket_index] == NULL){
        ht->lists[bucket_index] = new_node;
    }
    // If value at bucket index already exists, insert node at head of list
    else{
        new_node->next = ht->lists[bucket_index];
        ht->lists[bucket_index] = new_node;
    }

    // Increment size by one
    ht->elems++;

    return;
}

/*
 * This function should search for a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, return the corresponding value (void*) of the element,
 * otherwise, return NULL
 *
 * Params:
 *   ht - the hash table into which to loop up for an element.  May not be NULL.
 *   key - the key of the element to search for
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 *
 * Return:
 *   Should return the value of the corresponding 'key' in the hash table .
 */
void* ht_lookup(struct ht* ht, void* key, int (*convert)(void*)){

    // Get bucket index and store value into node
    int bucket_index = hash(key, ht->size);
    struct node* node = ht->lists[bucket_index];
    
    // Traverse list
    while(node != NULL){
        if(!strcmp(key, node->key)){
            return node->val;
        }
        node = node->next;
    }

    // If cannot find node with key, return NULL
    return NULL;
}


/*
 * This function should remove a given element in a hash table with a
 * specified key provided.   
 * This function is passed a function pointer that is used to convert the key (void*) 
 * to a unique hashcode (int). 
 * If the key is found, remove the element and return, otherwise, do nothing and return 
 *
 * Params:
 *   ht - the hash table into which to remove an element.  May not be NULL.
 *   key - the key of the element to remove
 *   convert - pointer to a function that can be passed the void* key from
 *     to convert it to a unique integer hashcode
 */
void ht_remove(struct ht* ht, void* key, int (*convert)(void*)){
    
    // Get bucket index
    int bucket_index = hash(key, ht->size);

    struct node* curr = ht->lists[bucket_index];
    struct node* prev = NULL;

    // If value to remove is already empty, return
    if (curr == NULL){
        return;
    }

    // Look for node to remove
    while(curr != NULL){
        if(!strcmp(key, curr->key)){
            // If node to remove is the head of list
            if(curr == ht->lists[bucket_index]){

                // Set new head to be next node
                ht->lists[bucket_index] = curr->next;
            }
            // If node to remove is not head
            else{

                // Set previous node to point to next node
                prev->next = curr->next;
            }

            // Free
            free(curr);
        }

        // Iterate through list
        prev = curr;
        curr = curr->next;
    }

    // Decrement elements stored by 1
    ht->elems--;

    return;
} 
