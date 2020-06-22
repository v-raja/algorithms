#include "graph.h"
#include "r_contract.h"
#include <stdlib.h> // For exit() function
#include <stdio.h>


void populate_graph_from_file(struct Graph* graph, struct Graph* graph_r, char* file);
void print_arr(int* arr, int size);
void output_arr(int* arr, int size, char* file);
int get_max_node_value(char* file);


int main(int argc, char* argv[])
{

  if (argc != 3)
  {
    printf("Usage: ./r_contract <in txt file> <output text file>\n");
    return -1;
  }

  int max = get_max_node_value(argv[1]);
  struct Graph* graph = create_graph(max);

  populate_graph_from_file(graph, argv[1]);
  int** scc_sizes = malloc(sizeof(int*));
  int num_scc = get_scc_sizes(graph, scc_sizes);
  output_arr(*scc_sizes, num_scc, argv[2]);
}

int get_max_node_value(char* file)
{
  FILE *fptr;
  if ((fptr = fopen(file, "r")) == NULL) {
    printf("Couldn't open file.");
    exit(1);
  }

  int src, dest = 0;
  int max = 0;
  while((fscanf(fptr, "%d<space>", &src) == 1) &&
        (fscanf(fptr, "%d\n", &dest) == 1))
  {
    if (max < src) max = src;
    if (max < dest) max = dest;
  }
  fclose(fptr);
  return max++;
}

void populate_graph_from_file(struct Graph* graph, char* file)
{
  FILE *fptr;

  if ((fptr = fopen(file, "r")) == NULL) {
    printf("Couldn't open file.");
    exit(1);
  }

  int src, dest = 0;
  while((fscanf(fptr, "%d<space>", &src) == 1) &&
        (fscanf(fptr, "%d\n", &dest) == 1))
  {
    add_edge(graph, src, dest);
  }

  fclose(fptr);
}


void print_arr(int* arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%i ", arr[i]);
  }
  printf("\n");
}

void output_arr(int* arr, int size, char* file)
{
  FILE *fptr;
  if ((fptr = fopen(file, "w")) == NULL) {
    printf("Couldn't open file.");
    exit(1);
  }
  for (int i = 0; i < size; i++)
  {
    fprintf(fptr, "%d\n", arr[i]);
  }
  fclose(fptr);

  printf("Output written to %s\n", file);
}
