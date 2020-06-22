#ifndef _KARATSUBA_H_
#define _KARATSUBA_H_

int k_multiply(int num_a, int num_b);
static int square(int x);
static int expt(int num, int pow);
static int my_ceil(int num, int div);
static void split_at(int num, int split_at_digit, int* first, int* rest);

#endif
