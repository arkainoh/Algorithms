#include <stdio.h>
#include <malloc.h>

typedef struct _advancedSegmentTree {
  int capacity, size, *data, *update;
} advancedSegmentTree;
typedef advancedSegmentTree* AdvancedSegmentTree;

void _put(AdvancedSegmentTree ast, int n, int s, int e, int idx, int data) {
  if(s == e) {
    ast->data[n] = data;
    return;
  }
  int m = (s + e) / 2;
  if(idx <= m) _put(ast, n * 2, s, m, idx, data);
  else _put(ast, n * 2 + 1, m + 1, e, idx, data);
  ast->data[n] = ast->data[n * 2] + ast->data[n * 2 + 1];
}

AdvancedSegmentTree newAdvancedSegmentTree(int size, int* data) {
  AdvancedSegmentTree ret = (AdvancedSegmentTree)malloc(sizeof(advancedSegmentTree));
  ret->size = size;
  for(ret->capacity = 1; ret->capacity < ret->size; ret->capacity *= 2);
  ret->data = (int*)malloc(sizeof(int) * ret->capacity * 2);
  ret->update = (int*)calloc(ret->capacity * 2, sizeof(int));
  for(int i = 0; i < ret->size; i++) _put(ret, 1, 0, ret->size - 1, i, data[i]);
  return ret;
}

void put(AdvancedSegmentTree ast, int idx, int data) {
  _put(ast, 1, 0, ast->size - 1, idx, data);
}

void propagate(AdvancedSegmentTree ast, int n, int s, int e) {
  if(ast->update[n]) {
    if(s != e) {
      ast->update[n * 2] += ast->update[n];
      ast->update[n * 2 + 1] += ast->update[n];
    }
    ast->data[n] += (e - s + 1) * ast->update[n];
    ast->update[n] = 0;
  }
}

void _updateAll(AdvancedSegmentTree ast, int n, int s, int e, int from, int to, int change) {
  propagate(ast, n, s, e);
  if(to < s || e < from) return;
  if(from <= s && e <= to) {
    ast->update[n] += change;
    propagate(ast, n, s, e);
    return;
  }
  int m = (s + e) / 2;
  _updateAll(ast, n * 2, s, m, from, to, change);
  _updateAll(ast, n * 2 + 1, m + 1, e, from, to, change);
  ast->data[n] = ast->data[n * 2] + ast->data[n * 2 + 1];
}
void update(AdvancedSegmentTree ast, int idx, int change) {
  _updateAll(ast, 1, 0, ast->size - 1, idx, idx, change);
}

void updateAll(AdvancedSegmentTree ast, int from, int to, int change) {
  _updateAll(ast, 1, 0, ast->size - 1, from, to, change);
}

int _query(AdvancedSegmentTree ast, int n, int s, int e, int from, int to) {
  propagate(ast, n, s, e);
  if(to < s || e < from) return 0;
  if(from <= s && e <= to) return ast->data[n];
  int m = (s + e) / 2;
  return _query(ast, n * 2, s, m, from, to) + _query(ast, n * 2 + 1, m + 1, e, from, to);
}

int query(AdvancedSegmentTree ast, int from, int to) {
  return _query(ast, 1, 0, ast->size - 1, from, to);
}

void printAdvancedSegmentTree(AdvancedSegmentTree ast) {
  int b = 1, cnt = 0;
  for(int i = 1; i < ast->capacity * 2; i++) {
    printf("%d ", ast->data[i]);
    if(++cnt == b) {
      b *= 2;
      cnt = 0;
      printf("\n");
    }
  }
}

void removeAdvancedSegmentTree(AdvancedSegmentTree ast) {
  free(ast->data);
  free(ast->update);
  free(ast);
  ast = NULL;
}

void testAdvancedSegmentTree() {
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  AdvancedSegmentTree ast = newAdvancedSegmentTree(8, a);
  printf("Initial status\n");
  printAdvancedSegmentTree(ast);
  put(ast, 3, 6);
  put(ast, 5, 4);
  printf("\nput(3, 6)\n");
  printf("put(5, 4)\n");
  printAdvancedSegmentTree(ast);
  printf("\nquery(%d, %d): %d\n", 0, 7, query(ast, 0, 7));
  printf("query(%d, %d): %d\n", 2, 6, query(ast, 2, 6));
  printf("query(%d, %d): %d\n", 1, 3, query(ast, 1, 3));
  printf("query(%d, %d): %d\n", 6, 7, query(ast, 6, 7));
  printf("query(%d, %d): %d\n", 4, 1, query(ast, 4, 1));
  
  printf("\nupdateAll(2, 6, -3)\n");
  printf("updateAll(1, 3, 2)\n");
  updateAll(ast, 2, 6, -3);
  updateAll(ast, 1, 3, 2);
  printAdvancedSegmentTree(ast);

  printf("\nquery(%d, %d): %d\n", 0, 7, query(ast, 0, 7));
  printf("query(%d, %d): %d\n", 2, 6, query(ast, 2, 6));
  printf("query(%d, %d): %d\n", 1, 3, query(ast, 1, 3));
  printf("query(%d, %d): %d\n", 6, 7, query(ast, 6, 7));
  printf("query(%d, %d): %d\n", 4, 1, query(ast, 4, 1));
  printf("query(%d, %d): %d\n", 3, 4, query(ast, 3, 4));

  printf("\nFinal status\n");
  printAdvancedSegmentTree(ast);

  removeAdvancedSegmentTree(ast);
}

int main() {
  testAdvancedSegmentTree();
  return 0;
}
