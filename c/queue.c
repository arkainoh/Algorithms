#include <stdio.h>
#define QSIZE 6

int head, tail;
int Q[QSIZE];

void initQ() {
  head = tail = 0;
}

void enQ(int x) {
  int next_idx = (tail + 1) % QSIZE;
  Q[tail] = x;
  tail = next_idx;
}

int deQ() {
  int prev_idx = head;
  head = (head + 1) % QSIZE;
  return Q[prev_idx];
}

int isFullQ() {
  return (tail + 1) % QSIZE == head;
}

int isEmptyQ() {
  return head == tail;
}

int testQ() {
  initQ();
  if(isEmptyQ()) printf("Queue is empty\n");
  else printf("Queue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isFullQ()) {
      enQ(i);
      printf("enQ(%d)\n", i);
    }
    else {
      printf("Queue is full\n");
      break;
    }
  }

  if(isEmptyQ()) printf("Queue is empty\n");
  else printf("Queue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyQ()) {
      printf("deQ(): %d\n", deQ());  
    }
    else {
      printf("Queue is empty\n");
      break;
    }
  }
  return 0;
}

int main() {
  testQ();
  return 0;
}