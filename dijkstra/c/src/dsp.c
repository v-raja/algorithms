#include "dsp.h"

int* compute_shortest_paths(struct Graph* graph)
{
  int num_nodes = graph->num_nodes;
  struct Heap* heap = init_heap(num_nodes);
  int* A = malloc(sizeof(int) * (num_nodes));
  for (int i = 0; i < num_nodes; i++)
    A[i] = MAX_DIST;
  A[1] = 0;
  expand_frontier(graph->nodes[1], A, heap);
  return A;
}

void expand_frontier(struct Node* last_node_added, int* A, struct Heap* heap)
{
  for (int i = 0; i < last_node_added->num_next; i++)
  {
    struct Node* next_node = last_node_added->next[i];
    int next_node_idx = next_node->idx;
    if (A[next_node_idx] != MAX_DIST) continue; // base case of node already explored
    int next_node_dist = last_node_added->next_dists[i];
    int dist = next_node_dist + A[last_node_added->idx];
    int key = get_key_of_node(heap, /*node label*/ next_node_idx);
    if (key != -1) // vertex already in heap
    {
      if (dist < key)
        update_key(heap, /*node label*/ next_node_idx, /*key*/ dist);
        // update_key updates a key in logn time with better constants than deleting and adding again
        // delete_node_from_heap(heap, next_node_idx);
        // add_to_heap(heap, dist, next_node);
    }
    else
    {
      add_to_heap(heap, /*key*/ dist, /*node*/ next_node);

    }
  }

  struct HeapNode* min_heap_node = get_min(heap);
  if (min_heap_node == NULL) return; // heap is empty, no more to expand
  struct Node* min_node = min_heap_node->node;
  A[min_node->idx] = min_heap_node->key;
  free(min_heap_node);
  return expand_frontier(min_node, A, heap);
}


