#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>
#include <graph.h>

struct Heap
{
  struct HeapNode** data;
  int* node_pos;      // position of node in heap. node_pos[1] is the position of vertex 1 in data.
  int size;
  int capacity;
};

struct HeapNode
{
  int key;
  struct Node* node;
};

struct Heap* init_heap(int num_nodes);
void add_to_heap(struct Heap* heap, int key, struct Node* node);
int get_key_of_node(struct Heap* heap, int node_idx);
void delete_node_from_heap(struct Heap* heap, int node_idx);
void update_key(struct Heap* heap, int node_idx, int new_key);
int check_heap(struct Heap* heap);


struct HeapNode* get_min(struct Heap* heap);
static void delete_min(struct Heap* heap);
static void resize_heap(struct Heap* heap);
static void bubble_down(struct Heap* heap, int pos_in_heap);
static int get_child(int pos);
static int get_parent(int pos);
static void swap(struct Heap* heap, int pos_a, int pos_b);
static void bubble_up(struct Heap* heap, int pos_in_heap);


#endif
