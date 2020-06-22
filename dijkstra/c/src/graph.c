#include "graph.h"

struct Graph* create_graph(int N)
{
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->nodes = malloc(sizeof(struct Node) * N);
  for (int i = 0; i < N; i++)
  {
    graph->nodes[i] = NULL;
  }
  graph->num_nodes = N;

  return graph;
}

static struct Node* add_node(struct Graph* graph, int idx)
{
  if (graph->nodes[idx] != NULL) return graph->nodes[idx];
  struct Node* node = malloc(sizeof(struct Node));
  node->idx = idx;
  node->next = NULL;
  node->next_dists = NULL;
  node->num_next = 0;
  graph->nodes[idx] = node;
  return node;
}

void add_edge(struct Graph* graph, int src, int dest, int dist)
{
  struct Node* dest_node = add_node(graph, dest);
  struct Node* src_node = add_node(graph, src);

  add_edge_to_node(src_node, dest_node, dist);
}

static void add_edge_to_node(struct Node* from, struct Node* to, int dist)
{
  int curr_num_next = from->num_next;
  from->next = realloc(from->next, (curr_num_next + 1) * sizeof(struct Node*));
  from->next_dists = realloc(from->next_dists, (curr_num_next + 1) * sizeof(int));
  from->next[curr_num_next] = to;
  from->next_dists[curr_num_next] = dist;
  from->num_next++;
}


void print_graph(struct Graph* graph)
{
  int N = graph->num_nodes;
  for (int i = 1; i < N; i++)
    print_node(graph->nodes[i]);
}

void print_node(struct Node* node)
{
  if (node == NULL) return;
  printf("%d -> ", node->idx);
  for (int i = 0; i < node->num_next; i++)
    printf("%d,%d ", node->next[i]->idx, node->next_dists[i]);
  printf("\n");
}
