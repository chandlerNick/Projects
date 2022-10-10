#ifndef SPARSE_ARRAY_H
#define SPARSE_ARRAY_H

#include <stdbool.h>


// A node in the linked list for the sparse array.
// Each node has a column index and a value.
// The list is always stored in order of increasing column index.
typedef struct node {
    int column_index;
    int value;
    struct node* next;
} node_t;

node_t* make_node(int column, int value, node_t* next);
bool node_get(node_t* node, int column, int* result);
node_t* node_set(node_t* node, int column, int value);

// A sparse array
typedef struct {
    node_t** rows;      // An array of columns, one for each row
    int maxrows;        // The max number of rows
    int maxcolumns;     // The max number of columns
} sparse_array_t;

void sa_init(sparse_array_t* sa, int maxrows, int maxcolumns);
bool sa_get(sparse_array_t* sa, int row, int column, int* result);
bool sa_set(sparse_array_t* sa, int row, int column, int value);
void sa_free(sparse_array_t* sa);
void sa_print(sparse_array_t* sa);

#endif // SPARSE_ARRAY_H
