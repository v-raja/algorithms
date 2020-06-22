#include "heap.h"

struct Heap* init_heap(int num_nodes)
{
  struct Heap* heap = malloc(sizeof(struct Heap));
  int capacity = 100;
  heap->data = malloc(sizeof(struct HeapNode*) * capacity);
  heap->size = 0;
  heap->capacity = capacity;
  for (int i = 0; i < capacity; i++)
    heap->data[i] = NULL;
  heap->node_pos = malloc(sizeof(int) * (num_nodes));
  for (int i = 0; i < num_nodes; i++)
    heap->node_pos[i] = -1;
  return heap;
}

void add_to_heap(struct Heap* heap, int key, struct Node* node)
{
  int curr_size = heap->size;
  if (curr_size == heap->capacity) resize_heap(heap);
  struct HeapNode* heap_node = malloc(sizeof(struct HeapNode));
  heap_node->node = node;
  heap_node->key = key;
  heap->data[curr_size] = heap_node;
  heap->node_pos[node->idx] = curr_size;
  heap->size++;
  bubble_up(heap, curr_size);
}

static void bubble_up(struct Heap* heap, int pos_in_heap)
{
  if (pos_in_heap == 0) return; // base case
  int key = heap->data[pos_in_heap]->key;
  int parent_pos = get_parent(pos_in_heap);
  int parent_key = heap->data[parent_pos]->key;
  if (parent_key > key)
  {
    swap(heap, pos_in_heap, parent_pos);
    bubble_up(heap, parent_pos);
  }
}


static void swap(struct Heap* heap, int pos_a, int pos_b)
{
  int node_a_idx = heap->data[pos_a]->node->idx;
  int node_b_idx = heap->data[pos_b]->node->idx;

  struct HeapNode tmp = *(heap->data[pos_a]);
  *(heap->data[pos_a]) = *(heap->data[pos_b]);
  *(heap->data[pos_b]) = tmp;

  heap->node_pos[node_a_idx] = pos_b;
  heap->node_pos[node_b_idx] = pos_a;
}

static int get_parent(int pos)
{
  return ((pos+1) / 2) - 1;
}

static int get_first_child(int pos)
{
  return (2 * (pos+1)) - 1;
}

void delete_node_from_heap(struct Heap* heap, int node_idx)
{
  int last_pos = heap->size - 1;
  int pos_to_del = heap->node_pos[node_idx];
  swap(heap, pos_to_del, last_pos);
  heap->node_pos[node_idx] = -1;
  free(heap->data[last_pos]);
  heap->data[last_pos] = NULL;
  heap->size--;
  bubble_up(heap, pos_to_del);
  bubble_down(heap, pos_to_del);
}

void update_key(struct Heap* heap, int node_idx, int new_key)
{
  int node_pos = heap->node_pos[node_idx];
  heap->data[node_pos]->key = new_key;
  bubble_up(heap, node_pos);
}

static void bubble_down(struct Heap* heap, int pos_in_heap)
{
  int child_a_pos = get_first_child(pos_in_heap);
  int size = heap->size;
  if (child_a_pos >= size) return; // base case of no children
  int key = heap->data[pos_in_heap]->key;
  int child_a_key = heap->data[child_a_pos]->key;
  if (child_a_pos == size - 1) // only one child
  {
    if (child_a_key < key)
    {
      swap(heap, pos_in_heap, child_a_pos);
      return bubble_down(heap, child_a_pos);
    }
  }
  else
  {
    int child_b_pos = child_a_pos + 1;
    int child_b_key = heap->data[child_b_pos]->key;
    if (child_a_key < key && child_a_key <= child_b_key)
    {
      swap(heap, pos_in_heap, child_a_pos);
      return bubble_down(heap, child_a_pos);
    }
    else if (child_b_key < key && child_b_key <= child_a_key)
    {
      swap(heap, pos_in_heap, child_b_pos);
      return bubble_down(heap, child_b_pos);
    }
  }
}

int get_key_of_node(struct Heap* heap, int node_idx)
{
  int node_pos = heap->node_pos[node_idx];
  if (node_pos == -1)
  {
    return -1;
  }
  else
  {
    return heap->data[node_pos]->key;
  }
}

static void resize_heap(struct Heap* heap)
{
  int curr_capacity = heap->capacity;
  int new_capacity = curr_capacity * 2;
  heap->data = realloc(heap->data, sizeof(struct HeapNode*) * new_capacity);
  heap->node_pos = realloc(heap->node_pos, sizeof(int) * new_capacity);
  for (int i = curr_capacity; i < new_capacity; i++)
    heap->data[i] = NULL;
  heap->capacity = new_capacity;
}


struct HeapNode* get_min(struct Heap* heap)
{
  if (heap->size == 0) return NULL; // heap is empty

  struct HeapNode* min_node = malloc(sizeof(struct HeapNode));
  min_node->node = heap->data[0]->node;
  min_node->key = heap->data[0]->key;
  delete_min(heap);

  return min_node;
}

int check_heap(struct Heap* heap)
{
  int size = heap->size;
  for (int i = 0; i < size; i++)
  {
    int child_a_pos = get_first_child(i);
    if (child_a_pos >= size) continue;
    if (child_a_pos == size - 1)
    {
      if (heap->data[i]->key > heap->data[child_a_pos]->key)
          return -1;
    }
    else
    {
      if (heap->data[i]->key > heap->data[child_a_pos]->key
          || heap->data[i]->key > heap->data[child_a_pos+1]->key)
          return -1;
    }
  }
  return 0;
}

static void delete_min(struct Heap* heap)
{
  int last_pos = heap->size - 1;
  swap(heap, 0, last_pos);
  heap->node_pos[heap->data[last_pos]->node->idx] = -1;
  free(heap->data[last_pos]);
  heap->data[last_pos] = NULL;
  heap->size--;
  bubble_down(heap, 0);
}
