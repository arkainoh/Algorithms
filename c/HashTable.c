#include <stdio.h>
#include <malloc.h>
#define BUCKETS 5

typedef struct _pair {
  int key, val;
} pair;

typedef struct _hashTable {
  pair bucket[BUCKETS];
  int valid[BUCKETS];
  int used[BUCKETS];
  int size;
} hashTable;
typedef hashTable* HashTable;

HashTable newHashTable() {
  HashTable ret = (HashTable)malloc(sizeof(hashTable));
  for(int i = 0; i < BUCKETS; i++) {
    ret->valid[i] = 0;
  }
  ret->size = 0;
  return ret;
}

int getHash(int data) {
  return data;
}

int getBucket(int key) {
  return getHash(key) % BUCKETS;
}

int isFullHashTable(HashTable ht) {
  return ht->size == BUCKETS;
}

int isEmptyHashTable(HashTable ht) {
  return !ht->size;
}

void add(HashTable ht, int key, int val) {
  int bucket = getBucket(key), exist = 0;
  while(ht->valid[bucket]) {
    if(ht->bucket[bucket].key == key) {
      exist = 1;
      break;
    }
    bucket = (bucket + 1) % BUCKETS;
  }

  pair p = {key, val};
  ht->bucket[bucket] = p;
  ht->valid[bucket] = 1;
  if(!exist) ht->size++;
}

int search(HashTable ht, int key) {
  int bucket = getBucket(key);
  int cnt = 0;
  while(ht->valid[bucket]) {
    if(cnt == BUCKETS) return -1;
    if(ht->bucket[bucket].key == key) return bucket;
    cnt++;
    bucket = (bucket + 1) % BUCKETS;
  }

  return -1;
}

void removeHashTable(HashTable ht) {
  free(ht);
  ht = NULL;
}

void testHashTable() {
  HashTable ht = newHashTable();
  if(isEmptyHashTable(ht)) printf("HashTable is empty\n");
  else printf("HashTable is not empty\n");

  pair p[] = {{1, 1}, {2, 2}, {3, 3}, {3, 26}, {4, 4}, {5, 5}, {5, 32}, {6, 6}};

  for(int i = 0; ; i++) {
    if(!isFullHashTable(ht)) {
      add(ht, p[i].key, p[i].val);
      printf("add(%d, %d)\n", p[i].key, p[i].val);
    }
    else {
      printf("HashTable is full\n");
      break;
    }
  }

  printf("<HashTable>\n");
  for(int i = 0; i < BUCKETS; i++) {
    if(ht->valid[i]) printf("(%d, %d) ", ht->bucket[i].key, ht->bucket[i].val);
  }
  printf("\n");

  printf("search(3): %d\n", search(ht, 3));
  printf("search(5): %d\n", search(ht, 5));
  printf("search(6): %d\n", search(ht, 6));

  removeHashTable(ht);
}

int main() {
  testHashTable();
  return 0;
}