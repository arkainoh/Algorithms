#include <stdio.h>
#define VERTICES 10
#define V 0
#define W 1

int N;
int WeightedAdjacentVertexMatrix[VERTICES + 1][VERTICES + 1][2];

void addEdge(int(*g)[VERTICES + 1][2], int from, int to, int weight) {
  g[from][++g[from][0][W]][V] = to;
  g[from][g[from][0][W]][W] = weight;
}

void printWeightedAdjacentVertexMatrix(int(*g)[VERTICES + 1][2]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int v = 1; v <= g[i][0][W]; v++) {
      printf("%d(%d) ", g[i][v][V], g[i][v][W]);
    }
    printf("\n");
  }
}

void testWeightedAdjacentVertexMatrix() {
  N = 6;
  int(*g)[VERTICES + 1][2] = WeightedAdjacentVertexMatrix;
  addEdge(g, 1, 2, 10);
  addEdge(g, 1, 3, 30);
  addEdge(g, 1, 4, 15);
  addEdge(g, 2, 5, 20);
  addEdge(g, 3, 6, 5);
  addEdge(g, 4, 3, 5);
  addEdge(g, 4, 6, 20);
  addEdge(g, 5, 6, 20);
  addEdge(g, 6, 4, 20);
  printWeightedAdjacentVertexMatrix(g);
}

int main() {
  testWeightedAdjacentVertexMatrix();
  return 0;
}
