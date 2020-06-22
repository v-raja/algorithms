#include "karatsuba.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  int num_x;
  int num_y;
  if ((argc != 3)                           ||
      (sscanf (argv[1], "%i", &num_x) != 1) ||
      (sscanf (argv[2], "%i", &num_y) != 1))
  {
    printf("Usage: ./karatsuba <int> <int>\n");
    return 1;
  }

  printf("%i\n", k_multiply(num_x, num_y));

  return 0;
}


