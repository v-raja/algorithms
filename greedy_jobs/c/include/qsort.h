#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include "sodium.h"

void q_sort(void* arr, size_t num_elem, size_t size, int (*compar)(const void*, const void*));
static void partition(void* arr, int l_idx, int r_idx, size_t size, int (*compar)(const void*, const void*));
// static void swap(void* px, void* py, size_t size);
void swap(void * a, void * b, size_t size);


#endif
