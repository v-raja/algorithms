#ifndef _R_CONTRACT_H_
#define _R_CONTRACT_H_

#include "graph.h"
#include "sodium.h"
#include <string.h>

int min_cut(int** graph);
int r_contract(int** graph);
void get_random_edge(int** graph, int* larger_node_idx, int* smaller_node_idx);
int* merge_nodes(int** graph, int larger_node_idx, int smaller_node_idx);
void update_graph(int** graph, int smaller_node_idx, int larger_node_idx);
void update_node(int** graph, int node_idx, int old_label, int new_label);
void print_arr(int* arr, int size);
void add_node(int** nodes, int node_to_add);


#endif

