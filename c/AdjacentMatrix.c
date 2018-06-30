#include <stdio.h>
#define VERTICES 10

int N;
int AdjacentMatrix[VERTICES + 1][VERTICES + 1];

void addEdge(int(*g)[VERTICES + 1], int from, int to) {
  g[from][++g[from][0]] = to;
}

void printAdjacentMatrix(int(*g)[VERTICES + 1]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int v = 1; v <= g[i][0]; v++) {
      printf("%d ", g[i][v]);
    }
    printf("\n");
  }
}

void testAdjacentMatrix() {
  N = 3;
  int(*g)[VERTICES + 1] = AdjacentMatrix;
  addEdge(g, 3, 1);
  addEdge(g, 2, 4);
  addEdge(g, 1, 2);
  addEdge(g, 1, 6);
  printAdjacentMatrix(g);
}

int main() {
  testAdjacentMatrix();
  return 0;
}
