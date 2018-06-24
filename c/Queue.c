#include <stdio.h>
#include <malloc.h>
#define QUEUE_SIZE 10

typedef struct _queue {
  int head, tail;
  int data[QUEUE_SIZE + 1];
} queue;
typedef queue* Queue;

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

int testQueue() {
  Queue q = newQueue();
  if(isEmptyQueue(q)) printf("Queue is empty\n");
  else printf("Queue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isFullQueue(q)) {
      enqueue(q, i);
      printf("enqueue(%d)\n", i);
    }
    else {
      printf("Queue is full\n");
      break;
    }
  }

  if(isEmptyQueue(q)) printf("Queue is empty\n");
  else printf("Queue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyQueue(q)) {
      printf("dequeue(): %d\n", dequeue(q));  
    }
    else {
      printf("Queue is empty\n");
      break;
    }
  }

  removeQueue(q);
  return 0;
}

int main() {
  testQueue();
  return 0;
}