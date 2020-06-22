#include "graph.h"

struct Graph* create_graph(int num_nodes)
{
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->N = num_nodes;
  graph->nodes = malloc(num_nodes * sizeof(struct Node));
  for (int i = 0; i < num_nodes; i++)
  {
    graph->nodes[i] = NULL;
  }
  return graph;
}

struct Node* create_node(int val)
{
  struct Node* new_node = malloc(sizeof(struct Node));
  new_node->val = val;
  new_node->explored = false;
  new_node->next = NULL;
  new_node->size_next = 0;
  return new_node;
}

void add_edge(struct Graph* graph, int src, int dest)
{
  if (graph->nodes[dest] == NULL)
    graph->nodes[dest] = create_node(dest);


  if (graph->nodes[src] == NULL)
    graph->nodes[src] = create_node(src);

  struct Node* src_node = graph->nodes[src];
  int size_next = src_node->size_next + 1;
  src_node->size_next = size_next;
  src_node->next = realloc(src_node->next, size_next * (sizeof(struct Node*)));
  src_node->next[size_next-1] = graph->nodes[dest];
}

void print_node(struct Node* node)
{
  printf("%d -> ", node->val);
  for (int i = 0; i < node->size_next; i++)
  {
    printf("%d, ", node->next[i]->val);
  }
  printf("\n");
}

void print_graph(struct Graph* graph)
{
  for (int i = 0; i < graph->N; i++)
  {
    if (graph->nodes[i] == NULL)
    {
      printf("%d: NULL\n", i);
    }
    else
    {
      print_node(graph->nodes[i]);
    }
  }
}
