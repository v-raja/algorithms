#include "hash_table.h"

typedef struct Entry {
  int_fast64_t key;
  struct Entry* next;
} Entry;


void htlib_init()
{
  if (a != -1) return; // a & b for hash function already initalized
  if (sodium_init() < 0) {
      fprintf(stderr, "libsodium couldn't be initialized\n");
      exit(-1);
      return;
  }
  a = (((int_fast64_t)randombytes_random() << 32) | randombytes_uniform(UINT32_MAX - 1)) + 1;
  a &= ~(1UL<< 63); // ensure a is positive. not sure if its required that a is > 0
  b = ((int_fast64_t)randombytes_random() << 32) | randombytes_random();
  b &= ~(1UL<< 63); // ensure b is positive. not sure if its required that b is > 0
}


HashTable* htlib_create(int capacity)
{
  if (a == -1)
  {
    fprintf(stderr, "hash table library not initialized. Call ht_init()\n");
    return NULL;
  }
  int cap_idx = -1;
  for (int i = 0; i < NUM_CAPACITIES_IDXs; i++)
  {
    if (capacity < HT_CAPACITIES[i])
    {
      cap_idx = i;
      break;
    }
  }
  if (capacity == -1)
  {
    fprintf(stderr, "required capacity of hash table too big\n");
    return NULL;
  }
  int ht_cap = HT_CAPACITIES[cap_idx];
  HashTable* ht_ptr = malloc(sizeof(HashTable));
  ht_ptr->data = malloc(sizeof(Entry*) * ht_cap);
  ht_ptr->capacity = ht_cap;
  ht_ptr->size = 0;
  for (int i = 0; i < capacity; i++)
  {
    ht_ptr->data[i] = NULL;
  }
  return ht_ptr;
}

int htlib_add(HashTable* ht, int_fast64_t key)
{
  int hash = compute_hash(ht, key);
  if (htlib_contains_hash(ht, key, hash)) return 0;

  Entry* new_entry = malloc(sizeof(Entry));
  new_entry->key = key;
  new_entry->next = ht->data[hash];
  ht->data[hash] = new_entry;
  ht->size++;
  return 1;
}

static int htlib_contains_hash(HashTable* ht, int_fast64_t key, int hash)
{
  Entry* entry = ht->data[hash];
  while (entry != NULL)
  {
    if (entry->key == key)
    {
      return 1;
    }
    else
    {
      entry = entry->next;
    }
  }
  return 0;
}

int htlib_contains(HashTable* ht, int_fast64_t key)
{
  int hash = compute_hash(ht, key);
  Entry* entry = ht->data[hash];
  while (entry != NULL)
  {
    if (entry->key == key)
    {
      return 1;
    }
    else
    {
      entry = entry->next;
    }
  }
  return 0;
}


static int compute_hash(HashTable* ht, int_fast64_t key)
{
  int hash = ((a*key + b) % LARGEST_LONG_PRIME) % ht->capacity;
  return hash;
}
