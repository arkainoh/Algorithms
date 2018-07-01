#include <stdio.h>
#include <malloc.h>
#define QUEUE_SIZE 10
#define INFINITY 0x7fffffff
#define VERTICES 10
#define V 0

int N;
int AdjacentMatrix[VERTICES + 1][VERTICES + 1];
int score[VERTICES + 1];

typedef struct _queue {
  int head, tail;
  int data[QUEUE_SIZE + 1];
} queue;
typedef queue* Queue;

Queue q;

Queue newQueue() {
  Queue ret = (Queue)malloc(sizeof(queue));
  ret->head = ret->tail = 0;
  return ret;
}

void enqueue(Queue q, int data) {
  int next_idx = (q->tail + 1) % (QUEUE_SIZE + 1);
  q->data[q->tail] = data;
  q->tail = next_idx;
}

int dequeue(Queue q) {
  int prev_idx = q->head;
  q->head = (q->head + 1) % (QUEUE_SIZE + 1);
  return q->data[prev_idx];
}

int isFullQueue(Queue q) {
  return (q->tail + 1) % (QUEUE_SIZE + 1) == q->head;
}

int isEmptyQueue(Queue q) {
  return q->head == q->tail;
}

void removeQueue(Queue q) {
  free(q);
  q = NULL;
}

void addEdge(int(*g)[VERTICES + 1], int from, int to) {
  g[from][++g[from][0]] = to;
}

void printAdjacentMatrix(int(*g)[VERTICES + 1]) {
  for(int i = 1; i <= N; i++) {
    printf("%d: ", i);
    for(int v = 1; v <= g[i][0]; v++) printf("%d ", g[i][v]);
    printf("\n");
  }
}

int GraphBFS(int start_point, int destination) {
  int(*g)[VERTICES + 1] = AdjacentMatrix;
  score[start_point] = 0;
  enqueue(q, start_point);
  while(!isEmptyQueue(q)) {
    int src = dequeue(q);
    for(int p = 1; p <= g[src][0]; p++) {
      if(score[g[src][p]] == -1) {
        score[g[src][p]] = score[src] + 1;
        if(g[src][p] == destination) return score[destination];
        enqueue(q, g[src][p]);
      }
    }
  }
  return -1;
}

void initScore() {
  for(int i = 1; i <= VERTICES; i++) score[i] = -1;
}

void printScore() {
  for(int i = 1; i <= N; i++) printf("%d ", score[i]);
  printf("\n");
}

void getTestGraph() {
  N = 6;
  int(*g)[VERTICES + 1] = AdjacentMatrix;
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 1, 4);
  addEdge(g, 2, 5);
  addEdge(g, 3, 6);
  addEdge(g, 4, 3);
  addEdge(g, 4, 6);
  addEdge(g, 5, 6);
  addEdge(g, 6, 4);
}

void testGraphBFS() {
  int start_point = 1, destination = 6;
  int sol;
  q = newQueue();
  getTestGraph();
  initScore();
  printAdjacentMatrix(AdjacentMatrix);
  printf("\nInitial status\n");
  printScore();
  sol = GraphBFS(start_point, destination);
  printf("\nAfter applying GraphBFS\n");
  printScore();
  printf("\nSolution: %d\n", sol);
  removeQueue(q);
}

int main() {
  testGraphBFS();
  return 0;
}
