#include "graph.h"
#include "r_contract.h"
#include <stdlib.h> // For exit() function
#include <stdio.h>


void populate_graph_from_file(int** graph, int** graph_orig, char* file);
// void print_arr(int* arr, int size);
// void output_arr(int* arr, int size, char* file);
int get_max_node_value(char* file);


int main(int argc, char* argv[])
{

  if (argc != 2)
  {
    printf("Usage: ./r_contract <in txt file>\n");
    return -1;
  }

  int max = get_max_node_value(argv[1]);
  int** graph = create_graph(max);
  int** graph_orig = create_graph(max);
  populate_graph_from_file(graph, graph_orig, argv[1]);
  int min_cuts = min_cut(graph);
  printf("Computed %d min cuts.\n", min_cuts);
}

int get_max_node_value(char* file)
{
  FILE *fptr;
  if ((fptr = fopen(file, "r")) == NULL) {
    printf("Couldn't open file.");
    exit(1);
  }

  int num = 0;
  int max = 0;
  while(fscanf(fptr, "%d<space>", &num) == 1)
  {
    if (max < num) max = num;
  }
  fclose(fptr);
  printf("max: %d\n", max);
  return max;
}

void populate_graph_from_file(int** graph, int** graph_orig, char* file)
{
  FILE *fptr;

  if ((fptr = fopen(file, "r")) == NULL) {
    printf("Couldn't open file.");
    exit(1);
  }

  int LINESZ = 2048;
  char buff[LINESZ];
  char* buff_ptr = buff;

  int src, dest, offset;
  while(fgets(buff, LINESZ, fptr))
  {
    buff_ptr = buff;
    sscanf(buff_ptr, "%d%n", &src, &offset);
    buff_ptr += offset;
    while (sscanf(buff_ptr, "%d%n", &dest, &offset) == 1)
    {
      buff_ptr += offset;
      add_edge(graph, src, dest);
      add_edge(graph_orig, src, dest);
    }
  }

  fclose(fptr);
}



// void print_arr(int* arr, int size)
// {
//   for (int i = 0; i < size; i++)
//   {
//     printf("%i ", arr[i]);
//   }
//   printf("\n");
// }

// void output_arr(int* arr, int size, char* file)
// {
//   FILE *fptr;
//   if ((fptr = fopen(file, "w")) == NULL) {
//     printf("Couldn't open file.");
//     exit(1);
//   }
//   for (int i = 0; i < size; i++)
//   {
//     fprintf(fptr, "%d\n", arr[i]);
//   }
//   fclose(fptr);

//   printf("Output written to %s\n", file);
// }
