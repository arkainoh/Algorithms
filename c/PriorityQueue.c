#include <stdio.h>
#include <malloc.h>
#define PQ_SIZE 10

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
    if(next_idx + 1 <= pq->size && pq->cmp(pq->data[next_idx + 1], pq->data[next_idx])) ++next_idx;

    if(pq->cmp(pq->data[next_idx], pq->data[idx])) swap(pq->data, idx, next_idx);
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
  return a > b;
}

int testPriorityQueue() {
  PriorityQueue pq = newPriorityQueue(cmp);
  if(isEmptyPriorityQueue(pq)) printf("PriorityQueue is empty\n");
  else printf("PriorityQueue is not empty\n");

  int testdata[] = {3, 7, 5, 2, 1, 9, 8, 4, 6, 10, 11};
  
  for(int i = 0; ; i++) {
    if(!isFullPriorityQueue(pq)) {
      enqueue(pq, testdata[i]);
      printf("enqueue(%d)\n", testdata[i]);
    }
    else {
      printf("PriorityQueue is full\n");
      break;
    }
  }

  if(isEmptyPriorityQueue(pq)) printf("PriorityQueue is empty\n");
  else printf("PriorityQueue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyPriorityQueue(pq)) {
      printf("dequeue(): %d\n", dequeue(pq));  
    }
    else {
      printf("PriorityQueue is empty\n");
      break;
    }
  }

  removePriorityQueue(pq);
  return 0;
}

int main() {
  testPriorityQueue();
  return 0;
}