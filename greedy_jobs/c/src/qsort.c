#include "qsort.h"

void q_sort(void* arr, size_t nelem, size_t size, int (*compar)(const void*, const void*))
{
  if (sodium_init() < 0) {
      /* panic! libsodium couldn't be initialized, it is not safe to use */
      return;
  }
  partition(arr, 0, nelem-1, size, compar);
}

static void partition(void* arr, int l_idx, int r_idx, size_t size, int (*compar)(const void*, const void*))
{
  if (l_idx >= r_idx) return;
  int p_idx = l_idx + randombytes_uniform(r_idx - l_idx);

  swap(&arr[l_idx * size], &arr[p_idx * size], size);
  void* p = &arr[l_idx * size];
  int b_idx = l_idx + 1; // index of the boundary between elements smaller than p and larger than p
  for (int j = l_idx + 1; j <= r_idx; j++)
  {
    // if (arr[j] < p)
    if (compar(&arr[j * size], p) == -1)
    {
      swap(&arr[b_idx * size], &arr[j * size], size);
      b_idx++;
    }
  }
  swap(&arr[(b_idx - 1) * size], &arr[l_idx * size], size);
  partition(arr, l_idx, b_idx - 2, size, compar);
  partition(arr, b_idx, r_idx, size, compar);
}


void swap(void * a, void * b, size_t size)
{
    unsigned char * p = a, * q = b, tmp;
    for (size_t i = 0; i != size; ++i)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}
