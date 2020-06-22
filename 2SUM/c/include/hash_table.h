#include <stdio.h>
#include <stdint.h>
#include "sodium.h"

typedef struct HashTable {
  struct Entry** data;
  int size;
  int capacity;
} HashTable;

#define NUM_CAPACITIES_IDXs 13
static int HT_CAPACITIES[NUM_CAPACITIES_IDXs] = {769, 1543, 3079, 6151, 12289, 24593, 49157,
                        98317, 196613, 393241, 786433, 1572869, 3145739};
#define LARGEST_LONG_PRIME 9223372036854775807
static uint_fast64_t a = -1;
static uint_fast64_t b;

void htlib_init();
HashTable* htlib_create(int capacity);
int htlib_add(HashTable* ht, int_fast64_t key);
static int htlib_contains_hash(HashTable* ht, int_fast64_t key, int hash);
int htlib_contains(HashTable* ht, int_fast64_t key);
static int compute_hash(HashTable* ht, int_fast64_t key);
