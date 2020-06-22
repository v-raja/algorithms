#ifndef _DSP_H_
#define _DSP_H_

#include "graph.h"
#include "heap.h"

#define MAX_DIST 1000000

int* compute_shortest_paths(struct Graph* graph);
void expand_frontier(struct Node* last_node_added, int* A, struct Heap* heap);





#endif
