#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>
#include <graph.h>

#define MAX_DIST 1000000

// define floor(log2 x) as the number of leading zeros in a signed int
#define FLR_LOG2(X) ((unsigned) (8*sizeof (int) - __builtin_clz((X)) - 1))

typedef struct
{
  int key;
  Node* node;
} HeapNode;

typedef struct
{
  HeapNode** data;
  int* node_pos;      // position of node in heap. node_pos[1] is the position of vertex 1 in data.
  int size;
  int capacity;
} Heap;

Heap* heaplib_create(int num_nodes);
Heap* init_heap(Graph* graph);

void heaplib_add(Heap* heap, int key, Node* node);
int heaplib_get_node_key(Heap* heap, int node_idx);
void heaplib_delete_node(Heap* heap, int node_idx);
void heaplib_update_key(Heap* heap, int node_idx, int new_key);
int heaplib_check_heap(Heap* heap);
HeapNode* heaplib_extract_min(Heap* heap);

static void delete_min(Heap* heap);
static void resize_heap(Heap* heap);
static void resize_heap_to_size(Heap* heap, int size);
static void bubble_down(Heap* heap, int pos_in_heap);
static int get_child(int pos);
static int get_parent(int pos);
static void swap(Heap* heap, int pos_a, int pos_b);
static void bubble_up(Heap* heap, int pos_in_heap);
static void heapify(Heap* heap);

static int expt(int base, int exp);
static int expt_iter(int base, int exp, int prod);


#endif
