#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
  int val;
  bool explored;
  struct Node** next;
  int size_next;
};

struct Graph {
  int N;                // num_nodes
  struct Node** nodes;
};

void add_edge(struct Graph* graph, int src, int dest);
struct Node* create_node(int val);
struct Graph* create_graph(int num_nodes);
void print_graph(struct Graph* graph);

#endif
