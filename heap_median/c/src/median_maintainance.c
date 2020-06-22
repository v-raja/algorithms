#include "median_maintainance.h"
#include <stdio.h>

void init_mm()
{
  heap_low = init_heap();
  heap_high = init_heap();
}

void mm_add_int(int k)
{
  if (!check_heap(heap_low))
    printf("heap_low invariant not\n");
  if (!check_heap(heap_high))
    printf("heap_high invariant not\n");
  if (!invariant_ok())
      printf("invariant not maintained\n");

  int size_l = heap_size(heap_low);
  int size_h = heap_size(heap_high);
  if ((size_l == 0 && size_h == 0) ||
        k >= get_min(heap_high)) // add to heap_high
  {
    add_to_heap(heap_high, k);
    if (size_h > size_l)
      transfer_median(heap_high, heap_low);
  }
  else // add to heap_low
  {
    add_to_heap(heap_low, -k);
    if (size_l > size_h)
      transfer_median(heap_low, heap_high);
  }
}

int mm_get_median()
{
  int size_l = heap_size(heap_low);
  int size_h = heap_size(heap_high);
  if (size_h == size_l || size_l > size_h)
  {
    return -get_min(heap_low);
  }
  else
  {
    return get_min(heap_high);
  }
}


static void transfer_median(int** from_heap, int** to_heap)
{
  add_to_heap(to_heap, -remove_min(from_heap));
}

static int invariant_ok()
{
  int size_l = heap_size(heap_low);
  int h_min = get_min(heap_high);
  for (int i = 0; i < size_l; i++)
  {
    if ((*heap_low)[i] >= h_min)
    {
      return 0;
    }
  }
  return 1;
}
