#include "graph.h"

Graph graphlib_create(int N)
{
  // Graph* graph = malloc(sizeof(Graph));
  Graph graph = {.nodes = malloc(sizeof(Node) * N), .num_nodes = N};
  // graph->nodes = malloc(sizeof(Node) * N);
  for (int i = 0; i < N; i++)
  {
    graph.nodes[i] = NULL;
  }
  // graph->num_nodes = N;

  return graph;
}

static Node* add_node(Graph* graph, int idx)
{
  if (graph->nodes[idx] != NULL) return graph->nodes[idx];
  Node* node = malloc(sizeof(Node));
  node->idx = idx;
  node->next = NULL;
  node->next_dists = NULL;
  node->num_next = 0;
  graph->nodes[idx] = node;
  return node;
}

void graphlib_add_edge(Graph* graph, int src, int dest, int dist)
{
  Node* dest_node = add_node(graph, dest);
  Node* src_node = add_node(graph, src);

  add_edge_to_node(src_node, dest_node, dist);
}

static void add_edge_to_node(Node* from, Node* to, int dist)
{
  int curr_num_next = from->num_next;
  from->next = realloc(from->next, (curr_num_next + 1) * sizeof(Node*));
  from->next_dists = realloc(from->next_dists, (curr_num_next + 1) * sizeof(int));
  from->next[curr_num_next] = to;
  from->next_dists[curr_num_next] = dist;
  from->num_next++;
}


void graphlib_print_graph(Graph* graph)
{
  int N = graph->num_nodes;
  for (int i = 1; i < N; i++)
    print_node(graph->nodes[i]);
}

static void print_node(Node* node)
{
  if (node == NULL) return;
  printf("%d -> ", node->idx);
  for (int i = 0; i < node->num_next; i++)
    printf("%d,%d ", node->next[i]->idx, node->next_dists[i]);
  printf("\n");
}


// TODO graph cost?
