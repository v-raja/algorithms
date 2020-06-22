#include "karatsuba.h"

int k_multiply(int num_x, int num_y)
{
  // assume x and y are of same length, and even in length, and positive
  // change mod to rem to make it work for negative ints
  int num_x_digit = 1;
  while( (num_x / expt(10, num_x_digit) != 0) ) num_x_digit++;
  int num_y_digit = 1;
  while( (num_x / expt(10, num_y_digit) != 0) ) num_y_digit++;

  if ((num_x_digit == 1) || (num_y_digit == 1))
  {
    return num_x * num_y;
  }
  int num_digit_half = (num_x_digit > num_y_digit) ?
                        my_ceil(num_x_digit, 2) :
                        my_ceil(num_x_digit, 2);

  int a, b, c, d;
  split_at(num_x, num_digit_half, &a, &b);
  split_at(num_y, num_digit_half, &c, &d);

  int ac = k_multiply(a, c);
  int bd = k_multiply(b, d);
  int ad_plus_bc = k_multiply(a + b, c + d) - ac - bd;

  return (ac * expt(10, num_digit_half * 2))
          + (ad_plus_bc * expt(10, num_digit_half))
          + bd;
}

static void split_at(int num, int split_at_digit, int* first, int* rest)
{
  int divisor = expt(10, split_at_digit);
  *first = num / divisor;
  *rest = num % divisor;
}

static int square(int x) {return x * x;}

static int expt(int num, int pow)
{
  if (pow == 0) return 1;
  if (pow % 2 == 0)
  {
    return square(expt(num, pow/2));
  }
  else
  {
    return num * expt(num, pow-1);
  }
}

static int my_ceil(int num, int div)
{
  return num/div + (num % div != 0);
}
