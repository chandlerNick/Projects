#ifndef SENTINEL_H_
#define SENTINEL_H_

#include <stdbool.h>


// A node has a key and a value, and is linked to the previous
// and next nodes.
//
// A node with a key of "Head" and a value of NULL is the Head node.
// A node with a key of "Sentinel" and a value of NULL is the Sentinel node
typedef struct node {
    char* key;
    char* value;
    struct node* previous;
    struct node* next;
} node_t;


// Allocate and return a node with the given string key and string value.
// together with the given previous and next values.
node_t* make_node(char* key, char* value, node_t* previous, node_t* next);


// A sentinel list has a head and tail
typedef struct {
    node_t* head;
    node_t* sentinel;
} sentinel_list_t;

// Allocate and return a pointer to an empty sentinel list.
sentinel_list_t* sl_new();

// Print a sentinel list. Useful for debugging
void sl_print(sentinel_list_t* sl);

// Return the number of items in the sentinel list
int sl_length(sentinel_list_t* sl);

// Insert a key with a given value in lexicographic order
void sl_insert(sentinel_list_t* sl, char* key, char* value);

// Return the value if the key is in the list, or NULL if not found
char* sl_lookup(sentinel_list_t* sl, char* key);

// Replace the key in the sentinel list with the new value.
// Return true if successful, or false if the key is not present
bool sl_replace(sentinel_list_t* sl, char* key, char* value);

// Delete the key and value in the sentinel list
// Return true if successful, or false if the key is not present
bool sl_delete(sentinel_list_t* sl, char* key);

// Free the sentinel list, deallocating all allocated memory
void sl_free(sentinel_list_t* sl);


#endif  // SENTINEL_H_
