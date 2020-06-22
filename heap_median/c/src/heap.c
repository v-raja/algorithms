#include "heap.h"

int** init_heap()
{
  int** heap = malloc(sizeof(int*));
  int capacity = 300;
  int* heap_data = malloc(sizeof(int) * (capacity + 2));
  *heap_data = capacity;
  heap_data[1] = 0; // size
  *heap = &heap_data[2];
  return heap;
}

void add_to_heap(int** heap, int key)
{
  int curr_size = (*heap)[-1];
  int capactiy = (*heap)[-2];
  if (curr_size == capactiy) {
    resize_heap(heap);
  }
  (*heap)[curr_size] = key;
  (*heap)[-1]++;
  bubble_up(heap, curr_size);
}

static void resize_heap(int** heap)
{
  (*heap) = &((*heap)[-2]);
  int curr_capacity = **heap;
  int new_capacity = curr_capacity * 2;
  int* tmp = realloc(*heap, sizeof(int) * (new_capacity + 2));
  if (tmp == NULL)
  {
    fprintf(stderr, "Could not reallocate heap.\n");
    exit(-1);
  }
  else
  {
    tmp[0] = new_capacity;
    *heap = &tmp[2];
  }
}

static void bubble_up(int** heap, int pos_in_heap)
{
  if (pos_in_heap == 0) return; // base case
  int key = (*heap)[pos_in_heap];
  int parent_pos = get_parent(pos_in_heap);
  int parent_key = (*heap)[parent_pos];
  if (parent_key > key)
  {
    swap(heap, pos_in_heap, parent_pos);
    bubble_up(heap, parent_pos);
  }
}


static void swap(int** heap, int pos_a, int pos_b)
{
  int tmp = (*heap)[pos_a];
  (*heap)[pos_a] = (*heap)[pos_b];
  (*heap)[pos_b] = tmp;
}

static int get_parent(int pos)
{
  return ((pos+1) / 2) - 1;
}

static int get_first_child(int pos)
{
  return (2 * (pos+1)) - 1;
}

int get_min(int** heap)
{
  // if (heap[-1] == 0) return NULL; // heap is empty

  return (*heap)[0];
}

int check_heap(int** heap)
{
  int size = (*heap)[-1];
  for (int i = 0; i < size; i++)
  {
    int child_a_pos = get_first_child(i);
    if (child_a_pos >= size) continue;
    if (child_a_pos == size - 1) // only one child
    {
      if ((*heap)[i] > (*heap)[child_a_pos])
        return -1;
    }
    else
    {
      if ((*heap)[i] > (*heap)[child_a_pos]
          || (*heap)[i] > (*heap)[child_a_pos + 1])
          return -1;
    }
  }
  return 1;
}

int remove_min(int** heap)
{
  int min = (*heap)[0];
  int last_pos = (*heap)[-1] - 1;
  swap(heap, 0, last_pos);
  (*heap)[-1]--;
  bubble_down(heap, 0);
  return min;
}

static void bubble_down(int** heap, int pos_in_heap)
{
  int child_a_pos = get_first_child(pos_in_heap);
  int size = (*heap)[-1];
  if (child_a_pos >= size) return; // base case of no children
  int key = (*heap)[pos_in_heap];
  int child_a_key = (*heap)[child_a_pos];
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
    int child_b_key = (*heap)[child_b_pos];
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

int heap_size(int** heap)
{
  return (*heap)[-1];
}
