
#include <stdio.h>
#include "median_maintainance.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("Usage: ./median <in.txt>\n");
    return -1;
  }

  init_mm();
  FILE* fptr;

  if ((fptr = fopen(argv[1], "r")) == NULL)
  {
    printf("Could not open input file.\n");
    return -1;
  }

  int median_sum = 0;
  int k;
  while (fscanf(fptr,"%d", &k) == 1)
  {
    mm_add_int(k);
    median_sum += mm_get_median();
  }

  printf("sum mod 10000: %d\n", median_sum % 10000);
}
