#include <stdio.h>
#define VERTICES 10

int N;
int WeightedAdjacentMatrix[VERTICES + 1][VERTICES + 1];

void addEdge(int(*g)[VERTICES + 1], int from, int to, int weight) {
  g[from][to] = weight;
}

void printWeightedAdjacentMatrix(int(*g)[VERTICES + 1]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int j = 1; j <= N; j++) if(g[i][j]) printf("%d(%d) ", j, g[i][j]);
    printf("\n");
  }
}

void testWeightedAdjacentMatrix() {
  N = 6;
  int(*g)[VERTICES + 1] = WeightedAdjacentMatrix;
  addEdge(g, 1, 2, 10);
  addEdge(g, 1, 3, 30);
  addEdge(g, 1, 4, 15);
  addEdge(g, 2, 5, 20);
  addEdge(g, 3, 6, 5);
  addEdge(g, 4, 3, 5);
  addEdge(g, 4, 6, 20);
  addEdge(g, 5, 6, 20);
  addEdge(g, 6, 4, 20);
  printWeightedAdjacentMatrix(g);
}

int main() {
  testWeightedAdjacentMatrix();
  return 0;
}