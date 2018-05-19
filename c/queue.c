#include <stdio.h>
#define QUEUE_SIZE 6

int head, tail;
int Queue[QUEUE_SIZE];

void initQueue() {
  head = tail = 0;
}

void enQueue(int x) {
  int next_idx = (tail + 1) % QUEUE_SIZE;
  Queue[tail] = x;
  tail = next_idx;
}

int deQueue() {
  int prev_idx = head;
  head = (head + 1) % QUEUE_SIZE;
  return Queue[prev_idx];
}

int isFullQueue() {
  return (tail + 1) % QUEUE_SIZE == head;
}

int isEmptyQueue() {
  return head == tail;
}

int testQueue() {
  initQueue();
  if(isEmptyQueue()) printf("Queue is empty\n");
  else printf("Queue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isFullQueue()) {
      enQueue(i);
      printf("enQueue(%d)\n", i);
    }
    else {
      printf("Queue is full\n");
      break;
    }
  }

  if(isEmptyQueue()) printf("Queue is empty\n");
  else printf("Queue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyQueue()) {
      printf("deQueue(): %d\n", deQueue());  
    }
    else {
      printf("Queue is empty\n");
      break;
    }
  }
  return 0;
}

int main() {
  testQueue();
  return 0;
}