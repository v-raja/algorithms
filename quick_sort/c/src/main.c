#include "quick_sort.h"
#include <stdio.h>
#include <stdlib.h> // For exit() function


void print_arr(int* arr, int size);
int* populate_arr_from_file(int* arr, int* size, char* file);

int main(int argc, char *argv[])
{
  int* size = malloc(sizeof(int));
  int* arr;
  if (argc == 2)
  {
    arr = populate_arr_from_file(arr, size, argv[1]);
    printf("size: %i\n", *size);
    // print_arr(arr, 6);
  }
  else
  {
    *size = argc - 1;
    arr = malloc(*size * sizeof(int));
    for (int i = 1; i < argc; i++)
    {
      if (sscanf(argv[i], "%i", &arr[i-1]) != 1)
      {
        printf("All arguments must be integers.\n");
        return 1;
      }
    }
  }
  quick_sort(arr, *size);
  print_arr(arr, *size);
  return 0;
}

int* populate_arr_from_file(int* arr, int* size, char* file)
{
  FILE *fptr;
  if ((fptr = fopen(file, "r")) == NULL) {
      printf("Couldn't open file.");
      exit(1);
  }
  int i = 0;
  int x;
  while(fscanf(fptr, "%d\n", &x) == 1)
  {
    arr = realloc(arr, (i+1)*sizeof(int));
    arr[i] = x;
    i++;
  }
  *size = i;
  fclose(fptr);
  return arr;
}

void print_arr(int* arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%i ", arr[i]);
  }
  printf("\n");
}
