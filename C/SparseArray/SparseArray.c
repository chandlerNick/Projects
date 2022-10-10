#include <stdio.h>
#include <stdlib.h>
#include "sparse_array.h"


// Return a new node with the given column index, value and next pointer
node_t* make_node(int column, int value, node_t* next) {
    node_t *newnode = (node_t *)malloc(sizeof(node_t));
    newnode->column_index = column;
    newnode->value = value;
    newnode->next = next;
    return newnode;
}

// Get a node from this linked list with the given column.
// Set *result to the value and return true if found, or
// return false if the value was not found in the list.
bool node_get(node_t* node, int column, int* result) {
    node_t *temp = node;
    while (temp != NULL) {
      if (temp->column_index == column) {
      // The node was found
        *result = temp->value;
        return true;
      }
      temp = temp->next;
    }
    // The node was not found
    return false;
}


// deletes node at specified column, returns head of given list
node_t* delete_node(node_t* node, int column) {
  node_t* temp = node;

  if (temp->column_index == column) {
    node_t* freenode = temp->next;
    free(temp);
    temp = freenode;
    node = temp;
    return node;
  }

  while (temp->next != NULL) {
    // if the next node's column is equal to the column delete it!
    if (temp->next->column_index == column) {
      node_t* freenode = temp->next->next;
      free(temp->next);
      temp->next = freenode;
      return node;
    } else {
      temp = temp->next;
    }
  }
  // node was not in the list, print and return head.
  return node;
}


// set-value: changes the value of a given node.
// NOTE: only used in node_set after we know:
// the node is in the list value !=0 and node != NULL
void setVal(node_t *node, int value, int column) {
  node_t *temp = node;
  while (temp->column_index != column) {
    temp = temp->next;
  }
  if (temp->column_index == column) {
    temp->value = value;
  }
  return;
}


// addNode: adds a node at the specified column returns a node pointer
// WORKS!
// node won't be null, won't be in the list, and value won't be 0
node_t* add_node(node_t* node, int column, int value) {
  if (node->column_index > column) {  // Adds a node at the very front
    node_t *temp = node;
    node_t *newnode = make_node(column, value, temp);
    temp = newnode;  // Set the node object to the newnode object
    return temp;
  } else {  // Go through the linked list, looking for the correct position
    node_t* temp = node;
    while (temp->next != NULL) {
      if (temp->next->column_index > column) {
        break;  // in proper position, between two column nodes -- stop the loop
      }
      temp = temp->next;
    }  // In proper position,
    // at the end of the list or between proper column indicies
    node_t* newnode = make_node(column, value, temp->next);
    temp->next = newnode;
    return node;
  }
}


// If the node with the column is in the list, set its value to the given
// value, else create a new node and insert it in the right position
// within the list.
node_t* node_set(node_t* node, int column, int value) {
  int *res = (int *) malloc(sizeof(int *));
  if (value == 0 && node == NULL) {
    free(res);
    return node;
  }
  if (value == 0 && node_get(node, column, res)) {  // delete node
    node = delete_node(node, column);
    free(res);
    return node;
  } else if (node == NULL) {  // Start list
    node = make_node(column, value, NULL);  // First node, next is null
    free(res);
    return node;
  } else if (node_get(node, column, res)) {  // update value
    *res = value;
    setVal(node, value, column);
    free(res);
    return node;
  } else {
    // value != zero, the node not in list, we are not adding first node.
    // add node -- write the add node method.
    node = add_node(node, column, value);
    free(res);
    return node;
  }
  // It should have added a node somewhere
  return NULL;
}


// Initialize a sparse array of the maximum number of rows and columns
// Each linked list is set to NULL for the empty list
void sa_init(sparse_array_t* sa, int maxrows, int maxcolumns) {
    int i;
    sa->maxrows = maxrows;
    sa->maxcolumns = maxcolumns;
    sa->rows = (node_t **) calloc(maxrows, sizeof(node_t));
    for (i = 0; i < maxrows; i++) {
      sa->rows[i] = NULL;
    }
    return;
}

// Get the value in the sparse array at the given row and column.
// Set *result to the value stored in the array and return true.
// If the array doesn't contain the element, return false
bool sa_get(sparse_array_t* sa, int row, int column, int* result) {
    int i, maxrows = sa->maxrows, maxcolumns = sa->maxcolumns;

    if (column > maxcolumns || row > maxrows) {  // Trying to search of of range
      return false;
    }
    if (node_get(sa->rows[row], column, result)) {  // Node was found
      return true;
    }
    // Node was not found
    return false;
}

// Set the value in th sparse array at the given row and column to the value.
// Return true if successful, or false if the row and column are out of bounds.
bool sa_set(sparse_array_t* sa, int row, int column, int value) {
    int i, result = 0, maxrows = sa->maxrows, maxcolumns = sa->maxcolumns;

    if (row > maxrows || column > maxcolumns) {  // Out of bounds!
      return false;
    }
  // If value is nonzero, add nodes
    if (value != 0) {
      if (sa->rows[row] == NULL) {
        sa->rows[row] = node_set(sa->rows[row], column, value);
      } else {
        if (column < sa->rows[row]->column_index) {
        // make the new node the head of the list.
          sa->rows[row] = node_set(sa->rows[row], column, value);
        } else {
          node_set(sa->rows[row], column, value);
        }
      }
    } else {
  // If value is zero, delete nodes
    if (sa->rows[row] == NULL) {
        return true;  // nothing to do, the node is already gone
      } else {
        if (column == sa->rows[row]->column_index) {  // delete first
          sa->rows[row] = node_set(sa->rows[row], column, value);
        } else {
          node_set(sa->rows[row], column, value);  // get rid of a node
        }
      }
    }

    if (sa->rows[row] != NULL) {  // Node was successfully added
      return true;
    }
    // Shouldn't get here normally
    return false;
}



void freeList(node_t* node) {
  if (node == NULL) {
    return;
  } else {
    freeList(node->next);
    free(node);
  }
}


// Free memory dynamically allocated for the sparse array
void sa_free(sparse_array_t* sa) {
  for (int i = 0; i < sa->maxrows; i++) {
    freeList(sa->rows[i]);
  }
  free(sa->rows);
  return;
}




void sa_print(sparse_array_t* sa) {
    printf("Matrix(0x%lx):\n", (unsigned long) sa);
    for (int i = 0; i < sa->maxrows; i++) {
        printf("\tRow(%2d): ", i);
        for (node_t* node = sa->rows[i]; node != NULL; node = node->next) {
            printf("Col(%2d):%d", node->column_index, node->value);
            if (node->next != NULL) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

// You need 0 valgrind errors. Maybe restart the program if you have time.
