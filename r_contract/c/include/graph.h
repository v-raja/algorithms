#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int** create_graph(int num_nodes);
void add_edge(int** graph, int src, int dest);
void print_node(int node_num, int* adj_nodes);
void print_graph(int** graph);
void output_graph(int** graph, char* file);
int** copy_graph(int** graph);
int count_edges(int** graph);


#endif
