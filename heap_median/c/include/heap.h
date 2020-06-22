#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>
#include <stdio.h>

int** init_heap();
void add_to_heap(int** heap, int key);
static void resize_heap(int** heap);
static void bubble_up(int** heap, int pos_in_heap);
static void swap(int** heap, int pos_a, int pos_b);
static int get_parent(int pos);
static int get_first_child(int pos);
int get_min(int** heap);
int check_heap(int** heap);
int remove_min(int** heap);
static void bubble_down(int** heap, int pos_in_heap);
int heap_size(int** heap);

#endif
