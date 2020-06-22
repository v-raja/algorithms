#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include "sodium.h"

void quick_sort(int* arr, int size);
static void partition(int* arr, int l_idx, int r_idx);
static void swap(int* x, int* y);

#endif
