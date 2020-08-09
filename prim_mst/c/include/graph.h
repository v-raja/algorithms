#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
  int idx;
  struct Node** next;
  int* next_dists;
  int num_next;
} Node;

typedef struct {
  Node** nodes;
  int num_nodes;
} Graph;

Graph graphlib_create(int N);
void graphlib_add_edge(Graph* graph, int src, int dest, int dist);
static Node* add_node(Graph* graph, int idx);
static void add_edge_to_node(Node* from, Node* to, int dist);

static void print_node(Node* node);
void graphlib_print_graph(Graph* graph);

#endif
