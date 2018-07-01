#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define START_POINT 'S'
#define DESTINATION 'D'
#define ROAD '.'
#define WALL '#'
#define CODE_ROAD -1
#define CODE_WALL -2
#define QUEUE_SIZE 1024

int M, N;
char** map;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

typedef struct _point {
  int x, y;
} point;

typedef struct _queue {
  int head, tail;
  point data[QUEUE_SIZE + 1];
} queue;
typedef queue* Queue;

Queue q;

Queue newQueue() {
  Queue ret = (Queue)malloc(sizeof(queue));
  ret->head = ret->tail = 0;
  return ret;
}

void enqueue(Queue q, point data) {
  int next_idx = (q->tail + 1) % (QUEUE_SIZE + 1);
  q->data[q->tail] = data;
  q->tail = next_idx;
}

point dequeue(Queue q) {
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

void initMap() {
  map = (char**)malloc(sizeof(char*) * M);
  for(int i = 0; i < M; i++) map[i] = (char*)malloc(sizeof(char) * N);
}

void removeMap() {
  for(int i = 0; i < M; i++) free(map[i]);
  free(map);
}

void printMap(point start_point, point destination) {
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      if(i == start_point.x && j == start_point.y) printf("%3c", START_POINT);
      else if(i == destination.x && j == destination.y) printf("%3c", DESTINATION);
      else 
        switch(map[i][j]) {
          case CODE_WALL:
            printf("%3c", WALL);
            break;
          case CODE_ROAD:
            printf("%3c", ROAD);
            break;
          default:
            printf("%3d", map[i][j]);
            break;
        }  
    }
    printf("\n");
  }
}

void preprocessMap(point* start_point, point* destination) {
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      switch(map[i][j]) {
        case WALL:
          map[i][j] = CODE_WALL;
          break;
        case ROAD:
          map[i][j] = CODE_ROAD;
          break;
        case START_POINT:
          (*start_point).x = i;
          (*start_point).y = j;
          break;
        case DESTINATION:
          (*destination).x = i;
          (*destination).y = j;
      }
    }
  }
}

void getTestMap() {
  M = N = 10;
  initMap();
  strcpy(map[0], "##.#.##..#");
  strcpy(map[1], "#S...#.#.#");
  strcpy(map[2], "####.#..##");
  strcpy(map[3], "#....#...#");
  strcpy(map[4], "#..##....#");
  strcpy(map[5], "#...#.....");
  strcpy(map[6], ".....#...#");
  strcpy(map[7], "#...#...##");
  strcpy(map[8], "....#..#D#");
  strcpy(map[9], "#........#");
}

int GridBFS(point start_point, point destination) {
  map[start_point.x][start_point.y] = 0;
  enqueue(q, start_point);
  while(!isEmptyQueue(q)) {
    point pos = dequeue(q);
    for(int p = 0; p < 4; p++) {
      point npos = {pos.x + dx[p], pos.y + dy[p]};
      if(npos.x < 0 || npos.x >= M || npos.y < 0 || npos.y >= N) continue;
      else if(npos.x == destination.x && npos.y == destination.y) return map[pos.x][pos.y] + 1;
      else if(map[npos.x][npos.y] == CODE_WALL) continue;
      else if(map[npos.x][npos.y] == CODE_ROAD) {
        map[npos.x][npos.y] = map[pos.x][pos.y] + 1;
        enqueue(q, npos);
      }
      else continue;
    }
  }
  return -1;
}

void testGridBFS() {
  point start_point, destination;
  int sol;
  q = newQueue();
  getTestMap();
  preprocessMap(&start_point, &destination);
  printf("         Initial status\n");
  printMap(start_point, destination);
  sol = GridBFS(start_point, destination);
  printf("\n       After applying GridBFS\n");
  printMap(start_point, destination);
  printf("\nSolution: %d\n", sol);
  removeQueue(q);
  removeMap();
}

int main() {
  testGridBFS();
  return 0;
}