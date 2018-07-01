#include <stdio.h>
#define VERTICES 10
#define FROM 0
#define TO 1
#define W 2

int N;
int WeightedAdjacentEdgeMatrix[VERTICES + 1][VERTICES + 1][3];

void addEdge(int(*g)[VERTICES + 1][3], int from, int to, int weight) {
  g[from][g[from][0][W]][FROM] = from;
  g[from][++g[from][0][W]][TO] = to;
  g[from][g[from][0][W]][W] = weight;
}

void printWeightedAdjacentEdgeMatrix(int(*g)[VERTICES + 1][3]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int v = 1; v <= g[i][0][W]; v++) printf("%d(%d) ", g[i][v][TO], g[i][v][W]);
    printf("\n");
  }
}

void testWeightedAdjacentEdgeMatrix() {
  N = 6;
  int(*g)[VERTICES + 1][3] = WeightedAdjacentEdgeMatrix;
  addEdge(g, 1, 2, 10);
  addEdge(g, 1, 3, 30);
  addEdge(g, 1, 4, 15);
  addEdge(g, 2, 5, 20);
  addEdge(g, 3, 6, 5);
  addEdge(g, 4, 3, 5);
  addEdge(g, 4, 6, 20);
  addEdge(g, 5, 6, 20);
  addEdge(g, 6, 4, 20);
  printWeightedAdjacentEdgeMatrix(g);
}

int main() {
  testWeightedAdjacentEdgeMatrix();
  return 0;
}
