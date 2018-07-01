#include <stdio.h>
#define VERTICES 10
int N, colors;
int AdjacentMatrix[VERTICES + 1][VERTICES + 1];
int color[VERTICES + 1];

void addEdge(int(*g)[VERTICES + 1], int from, int to) {
  g[from][++g[from][0]] = to;
}

int isPossible(int v, int c) {
  for(int i = 1; i <= AdjacentMatrix[v][0]; i++) if(color[AdjacentMatrix[v][i]] == c) return 0;
  return 1;
}

int BackTracking(int s, int e) {
  if(s > e) return 1;
  for(int c = 1; c <= colors; c++) {
    if(isPossible(s, c)) {
      color[s] = c;
      if(BackTracking(s + 1, e)) return 1;
      color[s] = 0;
    }
  }
  return 0;
}

void printColors() {
  for(int i = 1; i <= N; i++) printf("%d ", color[i]);
  printf("\n");
}

void getTestGraph() {
  N = 4;
  colors = 3;
  int(*g)[VERTICES + 1] = AdjacentMatrix;
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 2, 1);
  addEdge(g, 2, 4);
  addEdge(g, 3, 1);
  addEdge(g, 3, 2);
  addEdge(g, 3, 4);
  addEdge(g, 4, 2);
  addEdge(g, 4, 3);
}

void testBackTracking() {
  getTestGraph();
  if(BackTracking(1, N)) {
    printf("Colors: ");
    printColors();
  } else printf("Not possible");
}

int main() {
  testBackTracking();
  return 0;
}