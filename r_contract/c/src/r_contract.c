#include "r_contract.h"


int min_cut(int** graph)
{
  int num_trials = *graph[0] * *graph[0];
  int min_cuts = graph[1][-1];
  for (int i = 0; i < num_trials; i++)
  {
    int** graph_copy = copy_graph(graph);
    int num_cuts = r_contract(graph_copy);
    // printf("%d: computed %d cuts\n", i, num_cuts);
    // print_graph(graph_copy);
    if (num_cuts < min_cuts) min_cuts = num_cuts;
  }
  return min_cuts;
}


int r_contract(int** graph)
{
  if (sodium_init() < 0)
    return -1; /* panic! libsodium couldn't be initialized, it is not safe to use */

  int size = *graph[0];
  int* larger_node_idx = malloc(sizeof(int));
  int* smaller_node_idx = malloc(sizeof(int));
  for (int i = 0; i < size-3; i++)
  // while (*graph[0] > 2)
  {
    get_random_edge(graph, larger_node_idx, smaller_node_idx);
    // printf("%d: contracting %d into %d\n", i, *smaller_node_idx, *larger_node_idx);

    graph[*larger_node_idx] = merge_nodes(graph, *larger_node_idx, *smaller_node_idx);
    update_graph(graph, *smaller_node_idx, *larger_node_idx);
  }
  return count_edges(graph);
}

void get_random_edge(int** graph, int* larger_node_idx, int* smaller_node_idx)
{
  // ensure that we don't pick a node that has been contracted here
  int rand_u = randombytes_uniform(*graph[0] - 1) + 1;

  int num_edges = graph[rand_u][-1];
  if (num_edges == -1) return get_random_edge(graph, larger_node_idx, smaller_node_idx);
  // assume every vertex has an edge
  int rand_edge = randombytes_uniform(num_edges);
  int rand_v = graph[rand_u][rand_edge];

  if (graph[rand_u][-1] > graph[rand_v][-1])
  {
    *larger_node_idx = rand_u;
    *smaller_node_idx = rand_v;
  } else {
    *larger_node_idx = rand_v;
    *smaller_node_idx = rand_u;
  }
}

void print_arr(int* arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%i ", arr[i]);
  }
  printf("\n");
}

void add_node(int** nodes, int node_to_add)
{
  // print_node(1, *nodes);
  int curr_size = (*nodes)[-1];
  // printf("size: %d\n", curr_size);
  (*nodes)--;
  *nodes = realloc(*nodes, (curr_size+2) * sizeof(int));
  (*nodes)++;
  (*nodes)[-1]++;
  (*nodes)[curr_size] = node_to_add;
  // return nodes;
}

int* merge_nodes(int** graph, int larger_node_idx, int smaller_node_idx)
{
  int* smaller_node = graph[smaller_node_idx];

  int size_new_larger_node = 0;
  int* new_larger_node = malloc((size_new_larger_node+1)*sizeof(int));
  *new_larger_node = size_new_larger_node;
  new_larger_node++;

  for (int i = 0; i < smaller_node[-1]; i++)
  {
    int node = smaller_node[i];
    if (node != larger_node_idx)
      add_node(&new_larger_node, node);
  }

  int* larger_node = graph[larger_node_idx];
  for (int i = 0; i < larger_node[-1]; i++)
  {
    int node = larger_node[i];
    if (node != smaller_node_idx)
      add_node(&new_larger_node, node);
  }
  return new_larger_node;
}

void update_node(int** graph, int node_idx, int old_label, int new_label)
{
  int* nodes = graph[node_idx];
  for (int i = 0; i < nodes[-1]; i++)
  {
    if (nodes[i] == old_label)
      nodes[i] = new_label;
  }
}

void update_graph(int** graph, int smaller_node_idx, int larger_node_idx)
{
  // iterate through next_nodes of smaller node (not including larger node)
  // change reference of smaller node to larger node
  // change size of smaller node in graph to -1 to indicate contraction


  int* smaller_node = graph[smaller_node_idx];

  for (int i = 0; i < smaller_node[-1]; i++)
  {
    int node_idx = smaller_node[i];
    if (node_idx != larger_node_idx)
    {
      update_node(graph, node_idx, smaller_node_idx, larger_node_idx);
    }
  }

  smaller_node[-1] = -1;
  // realloc(smaller_node, 0);
  // free(smaller_node);
}


int count_edges(int** graph)
{
  for (int i = 1; i < *graph[0]; i++)
  {
    if (graph[i][-1] != -1) return graph[i][-1];
  }
  return -2;
}
