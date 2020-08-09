#include "mst.h"

Graph* compute_mst(Graph* graph)
{
  Heap* heap = heaplib_create_from_graph(graph);
  Graph* mst = malloc(sizeof(Graph));
  expand_frontier(graph->nodes[1], heap, mst);
  return mst;
}

void expand_frontier(Node* last_node_added, Heap* heap, Graph* mst)
{
  for (int i = 0; i < last_node_added->num_next; i++)
  {
    Node* next_node = last_node_added->next[i];
    int next_node_idx = next_node->idx;
    if (A[next_node_idx] != MAX_DIST) continue; // base case of node already explored
    int next_node_dist = last_node_added->next_dists[i];
    int dist = next_node_dist + A[last_node_added->idx];
    int key = heaplib_get_node_key(heap, /*node label*/ next_node_idx);
    if (key != -1) // vertex already in heap
    {
      if (dist < key)
        heaplib_update_key(heap, /*node label*/ next_node_idx, /*key*/ dist);
        // update_key updates a key in logn time with better constants than deleting and adding again
        // heaplib_delete_node(heap, next_node_idx);
        // heaplib_add(heap, dist, next_node);
    }
    else
    {
      heaplib_add(heap, /*key*/ dist, /*node*/ next_node);

    }
  }

  HeapNode* min_heap_node = heaplib_extract_min(heap);
  if (min_heap_node == NULL) return; // heap is empty, no more to expand
  Node* min_node = min_heap_node->node;
  A[min_node->idx] = min_heap_node->key;
  free(min_heap_node);
  return expand_frontier(min_node, A, heap);
}


