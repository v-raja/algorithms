#ifndef _SCC_H_
#define _SCC_H_

#include "graph.h"

int get_scc_sizes(struct Graph* graph, struct Graph* graph_r, int** sizes_to_ret);
void DFS_calc_node_order_loop(struct Graph* graph_r);
void DFS_calc_node_order(struct Node* node_s);
void DFS_get_scc_loop(struct Graph* graph);
void DFS_get_scc(struct Node* node_s);

#endif

