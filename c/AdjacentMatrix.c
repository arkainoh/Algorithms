#include <stdio.h>
#define VERTICES 10

int AdjacentMatrix[VERTICES + 1][VERTICES + 1];

void addEdge(int(*g)[VERTICES + 1], int from, int to) {
  g[from][++g[from][0]] = to;
}

void testAdjacentMatrix() {
  int(*g)[VERTICES + 1] = AdjacentMatrix;
  addEdge(g, 3, 1);
  addEdge(g, 2, 4);
  addEdge(g, 1, 2);
  addEdge(g, 1, 6);
  for(int i = 1; i <= VERTICES; i++) {
    printf("%d: ", i);
    for(int v = 1; v <= AdjacentMatrix[i][0]; v++) {
      printf("%d ", AdjacentMatrix[i][v]);
    }
    printf("\n");
  }
}

int main() {
  testAdjacentMatrix();
  return 0;
}
