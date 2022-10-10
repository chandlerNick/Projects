#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sentinel.h"



// MakeCopy: makes a copy of the key, value, prev, and next.
node_t* make_node(char* key, char* value, node_t* previous, node_t* next) {
  node_t* newnode = (node_t *) malloc(sizeof(node_t));
  if (key != NULL) {
    newnode->key = strdup(key);
  } else {
    newnode->key = NULL;
  }
  if (value != NULL) {
    newnode->value = strdup(value);
  } else {
    newnode->value = NULL;
  }
  newnode->next = next;
  newnode->previous = previous;
  return newnode;
}


// Allocate and return a pointer to an empty sentinel list
sentinel_list_t* sl_new() {
  sentinel_list_t* newList = (sentinel_list_t *) \
  malloc(sizeof(sentinel_list_t));

  newList->head = make_node("Head", NULL, NULL, NULL);
  newList->sentinel = make_node("Sentinel", NULL, NULL, NULL);
  newList->sentinel->previous = newList->head;
  newList->head->next = newList->sentinel;

  return newList;
}

// Print a sentinel list. Useful for debugging
void sl_print(sentinel_list_t* sl) {
    printf("[");
    for (node_t* node = sl->head->next; node != sl->sentinel;
        node = node->next) {
        printf("(key=%s,value=%s), ", node->key, node->value);
    }
    printf("]\n");
}

// Return the number of items in the sentinel list
int sl_length(sentinel_list_t* sl) {
  int numItems = 0;
  node_t* temp = sl->head;

  while (strcmp(temp->next->key, "Sentinel") != 0) {
    numItems++;
    temp = temp->next;
  }

  return numItems;
}


// Locate Node: returns a node_t* to the node at a specific key.
// Returns NULL if the node is not found
node_t* locateNode(sentinel_list_t* sl, char* key) {
  node_t* temp = sl->head;
  char* tempKey;

  while (strcmp(temp->key, "Sentinel") != 0) {
    if (strcmp(temp->key, key) == 0) {  // Found the node.
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}




// Insert a key with a given value in lexicographic order
// Key and value are never NULL.
void sl_insert(sentinel_list_t* sl, char* key, char* value) {
  node_t* temp;
  int strcmpNum;

  if (sl_lookup(sl, key) != NULL) {  // The node is in the list
    if (sl_replace(sl, key, value)) {  // The key's value should be altered.
        return;
    } else {
        fprintf(stderr, "The node was not replaced.\n");
        exit(1);
    }
  } else {  // The node is not in the list
    // iterate through until in the proper position
    temp = sl->head;
    if (strcmp(temp->next->key, "Sentinel") != 0) {
      // List has more than 0 nodes
      while ((strcmpNum = strcmp(key, temp->next->key)) > 0){
        if (strcmp(temp->next->key, "Sentinel") == 0) {
          break;
        }
        temp = temp->next;
      }  // Once the desired key is less than the next key -- stop and add.
    }
    // create newnode after current node
    node_t* newnode = make_node(key, value, temp, temp->next);
    // update all pointers -- potentially need a placeholder with the next node.
    temp->next->previous = newnode;  // set the current temp->next to new node
    temp->next = newnode;  // set the old temp->next->previous to newnode
  }
  return;
}

// Return the value if the key is in the list, or NULL if not found
char* sl_lookup(sentinel_list_t* sl, char* key) {
  node_t* nodeOfInterest = locateNode(sl, key);
  if (nodeOfInterest == NULL) {  // Node not found!
    return NULL;
  }
  if (strcmp(nodeOfInterest->key, key) == 0) {  // Node found!
    return nodeOfInterest->value;
  }
  return NULL;
}

// Replace the key in the sentinel list with the new value.
// Return true if successful, or false if the key is not present
bool sl_replace(sentinel_list_t* sl, char* key, char* value) {
  node_t* nodeOfInterest;

  if (sl_lookup(sl, key) == NULL) {  // Node is not in the list
    return false;
  }

  nodeOfInterest = locateNode(sl, key);
  if (value != NULL) {
    free(nodeOfInterest->value);
    nodeOfInterest->value = strdup(value);
  } else {
    nodeOfInterest->value = NULL;
  }
  return true;
}

// Delete the key and value in the sentinel list
// Return true if successful, or false if the key is not present
bool sl_delete(sentinel_list_t* sl, char* key) {
  node_t* nodeOfInterest;

  if (sl_lookup(sl, key) == NULL) {  // Key not in list
    return  false;
  }
  // Key in list
  nodeOfInterest = locateNode(sl, key);
  // update pointers
  node_t* temp = nodeOfInterest->previous;

  nodeOfInterest->previous->next = nodeOfInterest->next;
  nodeOfInterest->next->previous = temp;

  nodeOfInterest->previous = NULL;
  nodeOfInterest->next = NULL;
  nodeOfInterest->key[0] = '\0';
  nodeOfInterest->value[0] = '\0';
  free(nodeOfInterest->key);
  free(nodeOfInterest->value);
  free(nodeOfInterest);
  return true;
}

// Free the sentinel list, deallocating all allocated memory
void sl_free(sentinel_list_t* sl) {
  node_t* temp = sl->head, *nodeOfInterest;


  while (strcmp(temp->next->key, "Sentinel") != 0) {
    sl_delete(sl, temp->next->key);
  }

  // Free the head and Sentinel
  nodeOfInterest = sl->head;
  nodeOfInterest->previous = NULL;
  nodeOfInterest->next = NULL;
  nodeOfInterest->key[0] = '\0';
  free(nodeOfInterest->key);

  nodeOfInterest = sl->sentinel;
  nodeOfInterest->previous = NULL;
  nodeOfInterest->next = NULL;
  nodeOfInterest->key[0] = '\0';
  free(nodeOfInterest->key);

  free(sl->head);
  free(sl->sentinel);
  free(sl);

  return;
}




// A small test program
int main() {
    // Feel free to modify this main program for your own testing

    sentinel_list_t* sl = sl_new();
    sl_print(sl);
    sl_insert(sl, "Princess", "Buttercup");
    sl_print(sl);
    sl_insert(sl, "Swordsman", "Inigo");
    sl_print(sl);
    sl_insert(sl, "Giant", "Fezzik");
    sl_print(sl);
    int len = sl_length(sl);
    printf("Length: %d\n", len);
    sl_replace(sl, "Princess", "Bride");
    sl_delete(sl, "Giant");
    sl_delete(sl, "Swordsman");
    sl_delete(sl, "Princess");
    sl_print(sl);
    sl_free(sl);

    return 0;
}
