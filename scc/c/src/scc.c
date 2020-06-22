#include "scc.h"

int finishing_time;
int scc_idx;
int* sizes;
int* finishing_order;

int get_scc_sizes(struct Graph* graph, struct Graph* graph_r, int** sizes_to_ret)
{
  DFS_calc_node_order_loop(graph_r);
  DFS_get_scc_loop(graph);
  *sizes_to_ret = sizes;

  return scc_idx + 1;
}

void DFS_calc_node_order_loop(struct Graph* graph_r)
{
  finishing_order = realloc(finishing_order, graph_r->N * sizeof(int));
  finishing_time = 0;
  int num_nodes = graph_r->N;
  // printf("No probl\n");
  for (int i = num_nodes - 1; i > 0; i--)
  {
    struct Node* node = graph_r->nodes[i];
    if (!(node->explored))
    {
      DFS_calc_node_order(node);
    }
  }
}

void DFS_calc_node_order(struct Node* node_s)
{
  node_s->explored = true;
  for (int i = 0; i < node_s->size_next; i++)
  {
    struct Node* node_v = node_s->next[i];
    if (!(node_v->explored))
    {
      DFS_calc_node_order(node_v);
    }
  }
  finishing_time++;
  finishing_order[finishing_time] = node_s->val;
}

void DFS_get_scc_loop(struct Graph* graph)
{
  scc_idx = -1;
  int num_nodes = graph->N;
  for (int i = num_nodes - 1; i > 0; i--)
  {
    struct Node* node = graph->nodes[finishing_order[i]];
    if (!node->explored)
    {
      scc_idx++;
      sizes = realloc(sizes, (scc_idx+1) * sizeof(int));
      sizes[scc_idx] = 0;
      DFS_get_scc(node);
    }
  }
}

void DFS_get_scc(struct Node* node_s)
{
  node_s->explored = true;
  sizes[scc_idx]++;
  for (int i = 0; i < node_s->size_next; i++)
  {
    struct Node* node_v = node_s->next[i];
    if (!node_v->explored)
    {
      DFS_get_scc(node_v);
    }
  }
}
