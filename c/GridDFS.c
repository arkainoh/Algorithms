#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define START_POINT 'S'
#define DESTINATION 'D'
#define ROAD '.'
#define WALL '#'
#define CODE_ROAD -1
#define CODE_WALL -2
#define STACK_SIZE 1024

int M, N;
char** map;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

typedef struct _point {
  int x, y;
} point;

typedef struct _stack {
  int top;
  point data[STACK_SIZE];
} stack;
typedef stack* Stack;

Stack s;

Stack newStack() {
  Stack s = (Stack)malloc(sizeof(stack));
  s->top = 0;
  return s;
}

void push(Stack s, point data) {
  s->data[s->top++] = data;
}

point pop(Stack s) {
  return s->data[--s->top];
}

int isFullStack(Stack s) {
  return s->top == STACK_SIZE;
}

int isEmptyStack(Stack s) {
  return s->top == 0;
}

void removeStack(Stack s) {
  free(s);
  s = NULL;
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

int GridDFS(point start_point, point destination) {
  map[start_point.x][start_point.y] = 0;
  push(s, start_point);
  while(!isEmptyStack(s)) {
    point pos = pop(s);
    for(int p = 0; p < 4; p++) {
      point npos = {pos.x + dx[p], pos.y + dy[p]};
      if(npos.x < 0 || npos.x >= M || npos.y < 0 || npos.y >= N) continue;
      else if(npos.x == destination.x && npos.y == destination.y) return map[pos.x][pos.y] + 1;
      else if(map[npos.x][npos.y] == CODE_WALL) continue;
      else if(map[npos.x][npos.y] == CODE_ROAD) {
        map[npos.x][npos.y] = map[pos.x][pos.y] + 1;
        push(s, npos);
      }
      else continue;
    }
  }
  return -1;
}

void testGridDFS() {
  point start_point, destination;
  int sol;
  s = newStack();
  getTestMap();
  preprocessMap(&start_point, &destination);
  printf("         Initial status\n");
  printMap(start_point, destination);
  sol = GridDFS(start_point, destination);
  printf("\n       After applying GridDFS\n");
  printMap(start_point, destination);
  printf("\nSolution: %d\n", sol);
  removeStack(s);
  removeMap();
}

int main() {
  testGridDFS();
  return 0;
}