#include "graph.h"


int** create_graph(int num_nodes)
{
  int* size = malloc(sizeof(int));
  *size = num_nodes + 1;
  int** graph = malloc(sizeof(int*) * (*size));
  graph[0] = size;
  for (int i = 1; i < *size; i++)
  {
    int* adj_nodes = malloc(sizeof(int));
    adj_nodes[0] = 0;    // store the size of the array in the first element
    // adj_nodes[1] = NULL;
    graph[i] = &adj_nodes[1];
  }
  return graph;
}

void add_edge(int** graph, int src, int dest)
{
  int curr_num_adj_nodes = graph[src][-1];
  graph[src]--;
  graph[src] = realloc(graph[src], (curr_num_adj_nodes + 2)*(sizeof(int)));
  graph[src]++;
  graph[src][-1]++;
  graph[src][curr_num_adj_nodes] = dest;
}

void print_node(int node_num, int* adj_nodes)
{
  if (adj_nodes[-1] == -1) return;
  printf("%d -> ", node_num);
  for (int i = 0; i < adj_nodes[-1]; i++)
  {
    printf("%d ", adj_nodes[i]);
  }
  printf("\n");
}

void print_graph(int** graph)
{
  int size = *graph[0];
  printf("size: %d\n", size);
  for (int i = 1; i < size; i++)
  {
    print_node(i, graph[i]);
  }
}

void output_graph(int** graph, char* file)
{
  FILE *fptr;
  if ((fptr = fopen(file, "w")) == NULL) {
    printf("Couldn't open file.");
    exit(1);
  }

  int size = *graph[0];
  for (int i = 1; i < size; i++)
  {
    // print_node(i, graph[i]);
    int size = graph[i][-1];
    if (size != -1)
    {
      fprintf(fptr, "%d ",  i);
      for (int j = 0; j < size; j++)
      {
        fprintf(fptr, "%d ",  graph[i][j]);
      }
      fprintf(fptr, "\n");
    }
  }
  fclose(fptr);

  printf("Output written to %s\n", file);
}

int** copy_graph(int** graph)
{
  int** new_graph = malloc(*graph[0]*sizeof(int*));
  // memcpy(new_graph, graph, (*graph[0]*sizeof(int*)));
  new_graph[0] = graph[0];
  // *new_graph = size;

  for (int i = 1; i < *graph[0]; i++)
  {
    int* node = &graph[i][-1];
    int* node_copy = malloc((*node+1) * sizeof(int));
    memcpy(node_copy, node, (*node + 1) * sizeof(int));
    new_graph[i] = &node_copy[1];
  }
  return new_graph;
}



