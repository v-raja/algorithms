#ifndef _DSP_H_
#define _DSP_H_

#include "graph.h"
#include "heap.h"

Graph* compute_mst(Graph* graph);
void expand_frontier(Node* last_node_added, Heap* heap, Graph* mst);





#endif
