#ifndef _MEDIAN_MAINTAINANCE_H_
#define _MEDIAN_MAINTAINANCE_H_

#include "heap.h"

static int** heap_low; // heap with smaller keys
static int** heap_high; // heap with larger keys
void init_mm();
void mm_add_int(int k);
int mm_get_median();
static void transfer_median(int** from_heap, int** to_heap);
static int invariant_ok();

#endif
