#include "mst.h"
#include <stdio.h>
#include "heap.h"

void populate_graph_from_file(Graph* graph, char* file);
int count_lines(char* file);
void write_arr_to_file(int* arr, int size, char* file);
void print_arr(int* arr, int size);
void print_ans(int* A);

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    printf("Error! Usage: ./dsp <graph.txt> <output.txt>\n");
    return -1;
  }

  char* graph_file = argv[1];
  Graph* graph = malloc(sizeof(Graph));
  populate_graph_from_file(graph, graph_file);
  graphlib_print_graph(graph);
  printf("log2 of %d is %d\n", 15, FLR_LOG2(15));
  printf("log2 of %d is %d\n", 8, FLR_LOG2(8));
  printf("log2 of %d is %d\n", 7, FLR_LOG2(7));
  printf("log2 of %d is %d\n", 19, FLR_LOG2(19));
  printf("log2 of %d is %d\n", 1, FLR_LOG2(1));
  // int* A = compute_shortest_paths(graph);
  // write_arr_to_file(A, num_nodes, argv[2]);
  return 0;
}

void populate_graph_from_file(Graph* graph, char* file)
{
  FILE* fptr;
  if ((fptr = fopen(file, "r")) == NULL)
  {
    printf("Couldn't open file.\n");
    exit(1);
  }

  int num_nodes;
  fscanf(fptr, "%d<space>", &num_nodes);
  num_nodes++; // start graph at vertex 1
  *graph = graphlib_create(num_nodes);
  fscanf(fptr, "%d\n", &num_nodes); // consume num_edges

  int src, dest, cost;
  while (fscanf(fptr, "%d<space>", &src) == 1 &&
        fscanf(fptr, "%d<space>", &dest) == 1 &&
        fscanf(fptr, "%d\n", &cost) == 1)
  {
    graphlib_add_edge(graph, src, dest, cost);
  }

  // int BUFFSZ = 2048;
  // char buff[BUFFSZ];
  // char* buff_ptr;

  // int src, dest, dist, offset;
  // while (fgets(buff, BUFFSZ, fptr))
  // {
  //   buff_ptr = buff;
  //   sscanf(buff_ptr, "%d%n", &src, &offset);
  //   buff_ptr += offset;
  //   while (sscanf(buff_ptr, " %d,%d%n", &dest, &dist, &offset) == 2)
  //   {
  //     add_edge(graph, src, dest, dist);
  //     buff_ptr += offset;
  //   }
  // }

  fclose(fptr);
}

int count_lines(char* file)
{
  FILE* fptr;
  if ((fptr = fopen(file, "r")) == NULL)
  {
    printf("Unable to open file.\n");
    exit(1);
  }

  int count = 0;
  char chr = getc(fptr);
  while (chr != EOF)
  {
    if (chr == '\n') count++;
    chr = getc(fptr);
  }
  fclose(fptr);

  return count;
}


void print_arr(int* arr, int size)
{
  for (int i = 1; i < size; i++)
    printf("%d: %d\n", i, arr[i]);
}

void write_arr_to_file(int* arr, int size, char* file)
{
  FILE* fptr;
  if ((fptr = fopen(file, "w")) == NULL)
  {
    printf("Unable to write to file.\n");
    exit(1);
  }
  for (int i = 1; i < size; i++)
    fprintf(fptr, "%d: %d\n", i, arr[i]);
}

void print_ans(int* A)
{
  int idx[10] = {7,37,59,82,99,115,133,165,188,197};
  for (int i = 0; i < 10; i++)
    printf("%d,",A[idx[i]]);
  printf("\n");
}
