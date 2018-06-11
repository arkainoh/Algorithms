#include <stdio.h>
#include <malloc.h>

typedef struct _segmentTree {
  int capacity, size, *data;
} segmentTree;
typedef segmentTree* SegmentTree;

SegmentTree newSegmentTree(int size, int* data) {
  int cnt = 0;
  SegmentTree ret = (SegmentTree)malloc(sizeof(segmentTree));
  ret->size = size;
  for(ret->capacity = 1; ret->capacity < ret->size; ret->capacity *= 2);
  ret->data = (int*)malloc(sizeof(int) * ret->capacity * 2);
  for(int i = ret->capacity; i < ret->capacity + ret->size; i++) ret->data[i] = data[cnt++];
  for(int i = ret->capacity + ret->size; i < ret->capacity * 2; i++) ret->data[i] = 0;  
  for(int i = ret->capacity - 1; i > 0; i--) ret->data[i] = ret->data[i * 2] + ret->data[i * 2 + 1];
  return ret;
}

void update(SegmentTree st, int idx, int data) {
  int iter = st->capacity + idx;
  st->data[iter] = data;
  for(iter = iter / 2; iter > 0; iter--) st->data[iter] = st->data[iter * 2] + st->data[iter * 2 + 1];
}

int query(SegmentTree st, int from, int to) {
  int ret = 0;
  from += st->capacity;
  to += st->capacity;
  for(; from < to; from /= 2, to /= 2) {
    if(from % 2) ret += st->data[from++];
    if(!(to % 2)) ret += st->data[to--];
  }

  if(from == to) ret += st->data[from];
  return ret;
}

void printSegmentTree(SegmentTree st) {
  int b = 1, cnt = 0;
  for(int i = 1; i < st->capacity * 2; i++) {
    printf("%d ", st->data[i]);
    if(++cnt == b) {
      b *= 2;
      cnt = 0;
      printf("\n");
    }
  }
}

void removeSegmentTree(SegmentTree st) {
  free(st->data);
  free(st);
  st = NULL;
}

void testSegmentTree() {
  int a[] = {1, 3, 2, 1, 4, 7, 6, 2, 8, 5};
  SegmentTree st = newSegmentTree(10, a);
  printf("Initial status\n");
  printSegmentTree(st);
  update(st, 3, 6);
  update(st, 5, 4);
  printf("\nupdate(3, 6)\n");
  printf("update(5, 4)\n");
  printSegmentTree(st);
  printf("\nquery(%d, %d): %d\n", 0, 9, query(st, 0, 9));
  printf("query(%d, %d): %d\n", 2, 6, query(st, 2, 6));
  printf("query(%d, %d): %d\n", 1, 3, query(st, 1, 3));
  printf("query(%d, %d): %d\n", 6, 9, query(st, 6, 9));
  printf("query(%d, %d): %d\n", 4, 1, query(st, 4, 1));
  removeSegmentTree(st);
}

int main() {
  testSegmentTree();
  return 0;
}
