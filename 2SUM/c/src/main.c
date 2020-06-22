#include "hash_table.h"


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    fprintf(stderr,"Error. Usage: ./2sum <<in txt file>>\n");
    return 0;
  }
  htlib_init();
  HashTable* ht = htlib_create(1200000);
  HashTable* target_ht = htlib_create(22000);

  FILE* fptr;

  if ((fptr = fopen(argv[1], "r")) == NULL)
  {
    printf("Could not open input file.\n");
    return -1;
  }

  int_fast64_t min_target = -10000;
  int_fast64_t max_target = 10000;
  int_fast64_t k;
  while (fscanf(fptr,"%lld", &k) == 1)
  {
    // printf("adding: %lld\n", k);
    if (htlib_add(ht, k))
    {
      int_fast64_t min_required_for_target = min_target - k;
      int_fast64_t max_required_for_target = max_target - k;
      for (int_fast64_t i = min_required_for_target; i <= max_required_for_target; i++)
      {
        if (htlib_contains(ht, i)) {
          int_fast64_t target = i + k;
          htlib_add(target_ht, target);
        }
      }
    }
  }

  printf("count: %d\n", target_ht->size);
  fclose(fptr);
}

