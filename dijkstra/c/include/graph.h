#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdlib.h>
#include <stdio.h>

struct Node {
  int idx; // TODO is this needed?
  struct Node** next;
  int* next_dists;
  int num_next;
};

struct Graph {
  struct Node** nodes;
  int num_nodes;
  // int size;
};

struct Graph* create_graph(int N);
void add_edge(struct Graph* graph, int src, int dest, int dist);
static struct Node* add_node(struct Graph* graph, int idx);
static void add_edge_to_node(struct Node* from, struct Node* to, int dist);

static void print_node(struct Node* node);
void print_graph(struct Graph* graph);

#endif
