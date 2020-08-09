#include "heap.h"

Heap* heaplib_create(int num_nodes)
{
  Heap* heap = malloc(sizeof(Heap));
  int capacity = 100;
  heap->data = malloc(sizeof(HeapNode*) * capacity);
  heap->size = 0;
  heap->capacity = capacity;
  for (int i = 0; i < capacity; i++)
    heap->data[i] = NULL;
  heap->node_pos = malloc(sizeof(int) * (num_nodes));
  for (int i = 0; i < num_nodes; i++)
    heap->node_pos[i] = -1;
  return heap;
}


Heap* heaplib_create_from_graph(Graph* graph)
{
  int num_nodes = graph->num_nodes;
  Heap* heap = heaplib_create(num_nodes);
  resize_heap_to_size(heap, num_nodes);
  for (int i = 0; i < num_nodes; i++)
  {
    HeapNode* new_node_p = malloc(sizeof(HeapNode));
    new_node_p->key = MAX_DIST;
    new_node_p->node = graph->nodes[i];
    heap->data[i] = new_node_p;
  }
  heap->size = num_nodes;
  heapify(heap);
  return heap;
}

static void heapify(Heap* heap)
{
  int size = heap->size;
  if (size == 1) return;
  int first_parent_pos = expt(2, FLR_LOG2(size)) - 1;
  for (int i = first_parent_pos; i >= 0; i--)
  {
    bubble_down(heap, i);
  }
}

static int expt(int base, int exp)
{
  return expt_iter(base, exp, 1);
}

static int expt_iter(int base, int exp, int prod)
{
  if (exp == 0) return prod;
  if (exp % 2 == 0) return expt_iter(base*base, exp / 2, prod);
  return expt_iter(base, exp - 1, prod * base);
}


void heaplib_add(Heap* heap, int key, Node* node)
{
  int curr_size = heap->size;
  if (curr_size == heap->capacity) resize_heap(heap);
  HeapNode* heap_node = malloc(sizeof(HeapNode));
  heap_node->node = node;
  heap_node->key = key;
  heap->data[curr_size] = heap_node;
  heap->node_pos[node->idx] = curr_size;
  heap->size++;
  bubble_up(heap, curr_size);
}

static void bubble_up(Heap* heap, int pos_in_heap)
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


static void swap(Heap* heap, int pos_a, int pos_b)
{
  int node_a_idx = heap->data[pos_a]->node->idx;
  int node_b_idx = heap->data[pos_b]->node->idx;

  HeapNode tmp = *(heap->data[pos_a]);
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

void heaplib_delete_node(Heap* heap, int node_idx)
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

void heaplib_update_key(Heap* heap, int node_idx, int new_key)
{
  int node_pos = heap->node_pos[node_idx];
  heap->data[node_pos]->key = new_key;
  bubble_up(heap, node_pos);
}

static void bubble_down(Heap* heap, int pos_in_heap)
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

int heaplib_get_node_key(Heap* heap, int node_idx)
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

static void resize_heap_to_size(Heap* heap, int size)
{
  int curr_capacity = heap->capacity;
  int new_capacity = size;
  heap->data = realloc(heap->data, sizeof(HeapNode*) * new_capacity);
  heap->node_pos = realloc(heap->node_pos, sizeof(int) * new_capacity);
  for (int i = curr_capacity; i < new_capacity; i++)
    heap->data[i] = NULL;
  heap->capacity = new_capacity;
}

static void resize_heap(Heap* heap)
{
  int curr_capacity = heap->capacity;
  int new_capacity = curr_capacity * 2;
  heap->data = realloc(heap->data, sizeof(HeapNode*) * new_capacity);
  heap->node_pos = realloc(heap->node_pos, sizeof(int) * new_capacity);
  for (int i = curr_capacity; i < new_capacity; i++)
    heap->data[i] = NULL;
  heap->capacity = new_capacity;
}


HeapNode* heaplib_extract_min(Heap* heap)
{
  if (heap->size == 0) return NULL; // heap is empty

  HeapNode* min_node = malloc(sizeof(HeapNode));
  min_node->node = heap->data[0]->node;
  min_node->key = heap->data[0]->key;
  delete_min(heap);

  return min_node;
}

int heaplib_check_heap(Heap* heap)
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

static void delete_min(Heap* heap)
{
  int last_pos = heap->size - 1;
  swap(heap, 0, last_pos);
  heap->node_pos[heap->data[last_pos]->node->idx] = -1;
  free(heap->data[last_pos]);
  heap->data[last_pos] = NULL;
  heap->size--;
  bubble_down(heap, 0);
}
