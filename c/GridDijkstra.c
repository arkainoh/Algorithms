#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define PQ_SIZE 10
#define INFINITY 0x7fffffff

int M, N;
int** map;
int** score;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

typedef struct _point {
  int x, y;
} point;

point** edgeTo;

void swap(point* arr, int i, int j) {
  point tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

typedef struct _priorityQueue {
  int size;
  point data[PQ_SIZE + 1];
  int(*cmp)(int, int);
} priorityQueue;
typedef priorityQueue* PriorityQueue;

PriorityQueue pq;

PriorityQueue newPriorityQueue(int(*cmp)(int, int)) {
  PriorityQueue ret = (PriorityQueue)malloc(sizeof(priorityQueue));
  ret->size = 0;
  ret->cmp = cmp;
  return ret;
}

void enqueue(PriorityQueue pq, point data) {
  pq->data[++pq->size] = data;

  for(int i = pq->size; i != 1; i /= 2) {
    if(pq->cmp(score[pq->data[i].x][pq->data[i].y], score[pq->data[i / 2].x][pq->data[i / 2].y])) {
      swap(pq->data, i, i / 2);
    } else break;
  }
}

point dequeue(PriorityQueue pq) {
  int idx = 1, next_idx;
  point ret = pq->data[idx];
  pq->data[idx] = pq->data[pq->size--];

  while(idx < pq->size) {
    if(idx * 2 > pq->size) break;
    next_idx = idx * 2;
    if(next_idx + 1 <= pq->size && pq->cmp(score[pq->data[next_idx + 1].x][pq->data[next_idx + 1].y], score[pq->data[next_idx].x][pq->data[next_idx].y])) ++next_idx;

    if(pq->cmp(score[pq->data[next_idx].x][pq->data[next_idx].y], score[pq->data[idx].x][pq->data[idx].y])) swap(pq->data, idx, next_idx);
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

void initGrid() {
  map = (int**)malloc(sizeof(int*) * M);
  score = (int**)malloc(sizeof(int*) * M);
  edgeTo = (point**)malloc(sizeof(point*) * M);
  for(int i = 0; i < M; i++) {
    map[i] = (int*)malloc(sizeof(int) * N);
    score[i] = (int*)malloc(sizeof(int) * N);
    edgeTo[i] = (point*)malloc(sizeof(point) * N);
  }
}

void removeGrid() {
  for(int i = 0; i < M; i++) {
    free(map[i]);
    free(score[i]);
    free(edgeTo[i]);
  }
  free(map);
  free(score);
  free(edgeTo);
}

void printMap() {
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) printf("%3d", map[i][j]);
    printf("\n");
  }
}

void initData() {
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      score[i][j] = INFINITY;
      edgeTo[i][j].x = i;
      edgeTo[i][j].y = j;
    }
  }
}

void printScore() {
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      if(score[i][j] == INFINITY) printf("  .");
      else printf("%3d", score[i][j]);
    }
    printf("\n");
  }
}

void getTestMap() {
  M = N = 3;
  initGrid();
  map[0][0] = 0; map[0][1] = 4; map[0][2] = 1;
  map[1][0] = 2; map[1][1] = 5; map[1][2] = 3;
  map[2][0] = 6; map[2][1] = 2; map[2][2] = 0;
  initData();
}

void printOptimalPath(point start_point, point destination) {
  point path[10], iter = destination;
  int top = 0;
  while(edgeTo[iter.x][iter.y].x != iter.x || edgeTo[iter.x][iter.y].y != iter.y) {
    path[top++] = iter;
    iter = edgeTo[iter.x][iter.y];
  }
  
  printf("(%d, %d)", start_point.x, start_point.y);
  while(top) {
    --top;
    printf(" -> (%d, %d)", path[top].x, path[top].y);
  }
  printf("\n");
}

int GridDijkstra(point start_point, point destination) {
  score[start_point.x][start_point.y] = 0;
  enqueue(pq, start_point);
  while(!isEmptyPriorityQueue(pq)) {
    point pos = dequeue(pq);
    if(pos.x == destination.x && pos.y == destination.y) return score[pos.x][pos.y];
    for(int p = 0; p < 4; p++) {
      point npos = {pos.x + dx[p], pos.y + dy[p]};
      if(npos.x < 0 || npos.x >= M || npos.y < 0 || npos.y >= N) continue;
      else if(score[npos.x][npos.y] > score[pos.x][pos.y] + map[npos.x][npos.y]) {
        score[npos.x][npos.y] = score[pos.x][pos.y] + map[npos.x][npos.y];
        edgeTo[npos.x][npos.y] = pos;
        enqueue(pq, npos);
      }
      else continue;
    }
  }
  return -1;
}

void testGridBFS() {
  int sol;
  pq = newPriorityQueue(cmp);
  getTestMap();
  point start_point = {0, 0}, destination = {M - 1, N - 1};
  printMap();
  printf("\nInitial status\n");
  printScore();
  sol = GridDijkstra(start_point, destination);
  printf("\nAfter applying GridDijkstra\n");
  printScore();
  printf("\nOptimal path from (%d, %d) to (%d, %d): ", start_point.x, start_point.y, destination.x, destination.y);
  printOptimalPath(start_point, destination);
  printf("\nSolution: %d\n", sol);
  removePriorityQueue(pq);
  removeGrid();
}

int main() {
  testGridBFS();
  return 0;
}