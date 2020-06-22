#include "gtest/gtest.h"

extern "C" {
  #include "quick_sort.h"
  #include "quick_sort.c" // need to include to test static functions
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *) a - *(int *) b);
}

TEST(QSortTest, SwapRandom) {
  // Create an array with random ints
  int size = 2913;
  int x[size];
  for (int i = 0 ; i < size; i++)
  {
    x[i] = randombytes_uniform(10000);
  }

  for (int i = 0; i < 5 * size; i++)
  {
    int idx_a = randombytes_uniform(size);
    int idx_b = randombytes_uniform(size);
    int orig_idx_a = x[idx_a];
    int orig_idx_b = x[idx_b];
    swap(&x[idx_a], &x[idx_b]);
    EXPECT_EQ(x[idx_a], orig_idx_b);
    EXPECT_EQ(x[idx_b], orig_idx_a);
  }
}


TEST(QSortTest, QuickSortRandom) {
  // Create an array with random ints
  int size = 32423;
  int x[size];
  for (int i = 0 ; i < size; i++)
  {
    x[i] = randombytes_uniform(238943);
  }

  int y[size];
  memcpy(y, x, sizeof(x));

  quick_sort(x, size);
  qsort(y, size, sizeof(int), cmpfunc);

  for (int i = 0; i < size; i++)
  {
    EXPECT_EQ(x[i], y[i]);
  }
}


int main(int argc, char **argv) {
  if (sodium_init() < 0) {
    printf("libsodium init failed\n");
    return 1;
  }

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
