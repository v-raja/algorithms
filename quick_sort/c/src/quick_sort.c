#include "quick_sort.h"

void quick_sort(int* arr, int size)
{
  if (sodium_init() < 0) {
      /* panic! libsodium couldn't be initialized, it is not safe to use */
      return;
  }
  partition(arr, 0, size-1);
}

static void partition(int* arr, int l_idx, int r_idx)
{
  if (l_idx >= r_idx) return;
  int p_idx = l_idx + randombytes_uniform(r_idx - l_idx);

  swap(&arr[l_idx], &arr[p_idx]);
  int p = arr[l_idx];
  int b = l_idx + 1; // index of the boundary between elements smaller than p and larger than p
  for (int j = l_idx + 1; j <= r_idx; j++)
  {
    if (arr[j] < p)
    {
      swap(&arr[b], &arr[j]);
      b++;
    }
  }
  swap(&arr[b - 1], &arr[l_idx]);
  partition(arr, l_idx, b - 2);
  partition(arr, b, r_idx);
}

static void swap(int* px, int* py)
{
  int tmp = *px;
  *px = *py;
  *py = tmp;
}


