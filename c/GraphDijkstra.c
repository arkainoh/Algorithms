#include <stdio.h>
#include <malloc.h>
#define PQ_SIZE 10
#define INFINITY 0x7fffffff
#define VERTICES 10
#define V 0
#define W 1

int N;
int WeightedAdjacentVertexMatrix[VERTICES + 1][VERTICES + 1][2];
int score[VERTICES + 1];
int edgeTo[VERTICES + 1];

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

typedef struct _priorityQueue {
  int size;
  int data[PQ_SIZE + 1];
  int(*cmp)(int, int);
} priorityQueue;
typedef priorityQueue* PriorityQueue;

PriorityQueue pq;

PriorityQueue newPriorityQueue(int(*cmp)(int, int)) {
  PriorityQueue ret = (PriorityQueue)malloc(sizeof(priorityQueue));
  ret->size = 0;
  ret->data[0] = 0;
  ret->cmp = cmp;
  return ret;
}

void enqueue(PriorityQueue pq, int data) {
  pq->data[++pq->size] = data;

  for(int i = pq->size; i != 1; i /= 2) {
    if(pq->cmp(pq->data[i], pq->data[i / 2])) {
      swap(pq->data, i, i / 2);
    } else break;
  }
}

int dequeue(PriorityQueue pq) {
  int idx = 1, next_idx, ret = pq->data[idx];
  pq->data[idx] = pq->data[pq->size--];

  while(idx < pq->size) {
    if(idx * 2 > pq->size) break;
    next_idx = idx * 2;
    if(next_idx + 1 <= pq->size && pq->cmp(score[pq->data[next_idx + 1]], score[pq->data[next_idx]])) ++next_idx;

    if(pq->cmp(score[pq->data[next_idx]], score[pq->data[idx]])) swap(pq->data, idx, next_idx);
    else break;
    idx = next_idx;
  }

  return ret;
}

int isFullPriorityQueue(PriorityQueue pq) {
  return pq->size == PQ_SIZE;
}

int isEmptyPriorityQueue(PriorityQueue pq) {
  return !pq->size;
}

void removePriorityQueue(PriorityQueue pq) {
  free(pq);
  pq = NULL;
}

int cmp(int a, int b) {
  return a < b;
}

void addEdge(int(*g)[VERTICES + 1][2], int from, int to, int weight) {
  g[from][++g[from][0][W]][V] = to;
  g[from][g[from][0][W]][W] = weight;
}

void printWeightedAdjacentVertexMatrix(int(*g)[VERTICES + 1][2]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int v = 1; v <= g[i][0][W]; v++) printf("%d(%d) ", g[i][v][V], g[i][v][W]);
    printf("\n");
  }
}

int GraphDijkstra(int start_point, int destination) {
  int(*g)[VERTICES + 1][2] = WeightedAdjacentVertexMatrix;
  score[start_point] = 0;
  enqueue(pq, start_point);
  while(!isEmptyPriorityQueue(pq)) {
    int src = dequeue(pq);
    if(src == destination) return score[destination];
    for(int p = 1; p <= g[src][0][W]; p++) {
      if(score[g[src][p][V]] > score[src] + g[src][p][W]) {
        score[g[src][p][V]] = score[src] + g[src][p][W];
        edgeTo[g[src][p][V]] = src;
        enqueue(pq, g[src][p][V]);
      }
    }
  }
  return -1;
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
  initData();
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
}

void getTestGraph2() {
  N = 5;
  initData();
  int(*g)[VERTICES + 1][2] = WeightedAdjacentVertexMatrix;
  addEdge(g, 1, 2, -1);
  addEdge(g, 1, 3, 4);
  addEdge(g, 2, 3, 3);
  addEdge(g, 2, 4, 2);
  addEdge(g, 2, 5, 2);
  addEdge(g, 4, 2, 1);
  addEdge(g, 4, 3, 5);
  addEdge(g, 5, 4, -3);
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

void testGraphDijkstra1() {
  printf("\nTest 1\n");
  int start_point = 1, destination = 6;
  int sol;
  pq = newPriorityQueue(cmp);
  getTestGraph1();
  printWeightedAdjacentVertexMatrix(WeightedAdjacentVertexMatrix);
  printf("\nInitial status\n");
  printScore();
  sol = GraphDijkstra(start_point, destination);
  printf("\nAfter applying GraphDijkstra\n");
  printScore();
  printf("\nOptimal path from %d to %d: ", start_point, destination);
  printOptimalPath(start_point, destination);
  printf("\nSolution: %d\n", sol);
  removePriorityQueue(pq);
}

void testGraphDijkstra2() {
  printf("\nTest 2\n");
  int start_point = 1, destination = 5;
  int sol;
  pq = newPriorityQueue(cmp);
  getTestGraph2();
  printWeightedAdjacentVertexMatrix(WeightedAdjacentVertexMatrix);
  printf("\nInitial status\n");
  printScore();
  sol = GraphDijkstra(start_point, destination);
  printf("\nAfter applying GraphDijkstra\n");
  printScore();
  printf("\nOptimal path from %d to %d: ", start_point, destination);
  printOptimalPath(start_point, destination);
  printf("\nSolution: %d\n", sol);
  removePriorityQueue(pq);
}

int main() {
  testGraphDijkstra1();
  testGraphDijkstra2();
  return 0;
}
