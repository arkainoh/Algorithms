#include <stdio.h>
#include <malloc.h>
#define PQ_SIZE 10
#define INFINITY 0x7fffffff
#define VERTICES 10
#define EDGES 10

int N;
int WeightedAdjacentMatrix[VERTICES + 1][VERTICES + 1];
int score[VERTICES + 1][VERTICES + 1];

void addEdge(int(*g)[VERTICES + 1], int from, int to, int weight) {
  g[from][to] = weight;
  score[from][to] = weight;
}

void printWeightedAdjacentMatrix(int(*g)[VERTICES + 1]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int j = 1; j <= N; j++) if(g[i][j]) printf("%d(%d) ", j, g[i][j]);
    printf("\n");
  }
}

void initData() {
  for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) score[i][j] = INFINITY;
}

void printScore() {
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++) {
      if(score[i][j] == INFINITY) printf("  . ");
      else printf("%3d ", score[i][j]);
    }
    printf("\n");
  }
}

void getTestGraph1() {
  N = 6;
  initData();
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
  initData();
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
  initData();
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

void FloydWarshall() {
  for(int k = 1; k <= N; k++)
    for(int i = 1; i <= N; i++)
      for(int j = 1; j <= N; j++)
        if(score[i][k] < INFINITY && score[k][j] < INFINITY && score[i][j] > score[i][k] + score[k][j])
          score[i][j] = score[i][k] + score[k][j];
}

void testFloydWarshall1() {
  printf("\nTest 1\n");
  int start_point = 1, destination = 6;
  getTestGraph1();
  printWeightedAdjacentMatrix(WeightedAdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  FloydWarshall(start_point);
  printf("\nAfter applying FloydWarshall\n");
  printScore();
  printf("\nSolution: %d\n", score[start_point][destination]);
}

void testFloydWarshall2() {
  printf("\nTest 2\n");
  int start_point = 1, destination = 5;
  getTestGraph2();
  printWeightedAdjacentMatrix(WeightedAdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  FloydWarshall(start_point);
  printf("\nAfter applying FloydWarshall\n");
  printScore();
  printf("\nSolution: %d\n", score[start_point][destination]);
}

void testFloydWarshall3() {
  printf("\nTest 3\n");
  int start_point = 1, destination = 5;
  getTestGraph3();
  printWeightedAdjacentMatrix(WeightedAdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  FloydWarshall(start_point);
  printf("\nAfter applying FloydWarshall\n");
  printScore();
  printf("\nSolution: %d\n", score[start_point][destination]);
}

int main() {
  testFloydWarshall1();
  testFloydWarshall2();
  testFloydWarshall3();
  return 0;
}