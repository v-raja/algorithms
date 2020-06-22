#include "gtest/gtest.h"
#include "sodium.h"
#include "math.h"

extern "C" {
  #include "karatsuba.h"
  #include "karatsuba.c" // need to include to test static functions
}

TEST(KTests, MultiplyRandom)
{
  for (int i = 0; i < 10000; i++)
  {
    int a = randombytes_uniform(100000);
    int b = randombytes_uniform(100000);
    EXPECT_EQ(a*b, k_multiply(a,b));
  }
}

TEST(KTests, PowerRandom)
{
  for (int i = 0; i < 100000; i++)
  {
    int a = randombytes_uniform(10);
    int b = randombytes_uniform(10);
    EXPECT_EQ(expt(a,b), pow(a,b));
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
