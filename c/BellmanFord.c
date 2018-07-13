#include <stdio.h>
#include <malloc.h>
#define PQ_SIZE 10
#define INFINITY 0x7fffffff
#define VERTICES 10
#define EDGES 10

int N;
int WeightedAdjacentMatrix[VERTICES + 1][VERTICES + 1];
int score[VERTICES + 1];
int edgeTo[VERTICES + 1];

typedef struct _edge {
  int from, to, weight;
} edge;

int num_edges = 0;
edge edges[EDGES];

void addEdge(int(*g)[VERTICES + 1], int from, int to, int weight) {
  g[from][to] = weight;
  edge e = { from, to, weight };
  edges[num_edges++] = e;
}

void printWeightedAdjacentMatrix(int(*g)[VERTICES + 1]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int j = 1; j <= N; j++) if(g[i][j]) printf("%d(%d) ", j, g[i][j]);
    printf("\n");
  }
}

void initData() {
  for(int i = 1; i <= N; i++) {
    score[i] = INFINITY;
    edgeTo[i] = i;
  }
}

void printScore() {
  for(int i = 1; i <= N; i++) {
    if(score[i] == INFINITY) printf(". ");
    else printf("%d ", score[i]);
  }
  printf("\n");
}

void getTestGraph1() {
  N = 6;
  num_edges = 0;
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
}

void getTestGraph2() {
  N = 5;
  num_edges = 0;
  int(*g)[VERTICES + 1] = WeightedAdjacentMatrix;
  addEdge(g, 1, 2, -1);
  addEdge(g, 1, 3, 4);
  addEdge(g, 2, 3, 3);
  addEdge(g, 2, 4, 2);
  addEdge(g, 2, 5, 2);
  addEdge(g, 4, 2, 1);
  addEdge(g, 4, 3, 5);
  addEdge(g, 5, 4, -3);
}

void getTestGraph3() {
  N = 5;
  num_edges = 0;
  int(*g)[VERTICES + 1] = WeightedAdjacentMatrix;
  addEdge(g, 1, 2, -1);
  addEdge(g, 1, 3, 4);
  addEdge(g, 2, 3, 3);
  addEdge(g, 2, 4, 2);
  addEdge(g, 2, 5, 2);
  addEdge(g, 4, 2, 1);
  addEdge(g, 4, 3, 5);
  addEdge(g, 5, 4, -4);
}

void BellmanFord(int start_point) {
  score[start_point] = 0;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < num_edges; j++) {
      edge e = edges[j];
      if(score[e.from] < INFINITY && score[e.to] > score[e.from] + e.weight) {
        score[e.to] = score[e.from] + e.weight;
        edgeTo[e.to] = e.from;
      }
    }
}

int detectNegativeCycle() {
  for(int i = 0; i < num_edges; i++) {
    edge e = edges[i];
    if(score[e.from] < INFINITY && score[e.to] < INFINITY && score[e.to] > score[e.from] + e.weight) return e.to;
  }
  return 0;
}

void printOptimalPath(int start_point, int destination) {
  int path[VERTICES];
  int iter, top = 0;
  iter = destination;
  while(edgeTo[iter] != iter) {
    path[top++] = iter;
    iter = edgeTo[iter];
  }
  printf("%d", start_point);
  while(top) printf(" -> %d", path[--top]);
  printf("\n");
}

void testBellmanFord1() {
  printf("\nTest 1\n");
  int start_point = 1, destination = 6, tmp;
  getTestGraph1();
  initData();
  printWeightedAdjacentMatrix(WeightedAdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  BellmanFord(start_point);
  printf("\nAfter applying BellmanFord\n");
  printScore();
  if(tmp = detectNegativeCycle()) printf("\n<WARNING> Negative cycle has been detected around %d\n", tmp);
  else {
    printf("\nNegative cycle has not been detected\n");
    printf("\nOptimal path from %d to %d: ", start_point, destination);
    printOptimalPath(start_point, destination);
    printf("\nSolution: %d\n", score[destination]);
  }
}

void testBellmanFord2() {
  printf("\nTest 2\n");
  int start_point = 1, destination = 5, tmp;
  getTestGraph2();
  initData();
  printWeightedAdjacentMatrix(WeightedAdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  BellmanFord(start_point);
  printf("\nAfter applying BellmanFord\n");
  printScore();
  if(tmp = detectNegativeCycle()) printf("\n<WARNING> Negative cycle has been detected around %d\n", tmp);
  else {
    printf("\nNegative cycle has not been detected\n");
    printf("\nOptimal path from %d to %d: ", start_point, destination);
    printOptimalPath(start_point, destination);
    printf("\nSolution: %d\n", score[destination]);
  }
}

void testBellmanFord3() {
  printf("\nTest 3\n");
  int start_point = 1, destination = 5, tmp;
  getTestGraph3();
  initData();
  printWeightedAdjacentMatrix(WeightedAdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  BellmanFord(start_point);
  printf("\nAfter applying BellmanFord\n");
  printScore();
  if(tmp = detectNegativeCycle()) printf("\n<WARNING> Negative cycle has been detected around %d\n", tmp);
  else {
    printf("\nNegative cycle has not been detected\n");
    printf("\nOptimal path from %d to %d: ", start_point, destination);
    printOptimalPath(start_point, destination);
    printf("\nSolution: %d\n", score[destination]);
  }
}

int main() {
  testBellmanFord1();
  testBellmanFord2();
  testBellmanFord3();
  return 0;
}