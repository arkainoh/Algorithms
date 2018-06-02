#include <stdio.h>
#include <malloc.h>

typedef struct _node* Node;
typedef struct _node {
  int data;
  Node prev, next;
} node;

typedef struct _dynamicQueue {
  Node head, tail;
  int size;
} dynamicQueue;
typedef dynamicQueue* DynamicQueue;

DynamicQueue newDynamicQueue() {
  DynamicQueue ret = (DynamicQueue)malloc(sizeof(dynamicQueue));
  ret->head = ret->tail = NULL;
  ret->size = 0;
  return ret;
}

Node newNode(int data, Node prev, Node next) {
  Node ret = (Node)malloc(sizeof(node));
  ret->data = data;
  ret->prev = prev;
  ret->next = next;
  return ret;
}

int isEmptyDynamicQueue(DynamicQueue dq) {
  return !dq->head;
}

void enqueue(DynamicQueue dq, int data) {
  if(!dq->head) dq->head = dq->tail = newNode(data, NULL, NULL);
  else {
    dq->tail->next = newNode(data, dq->tail, NULL);
    dq->tail = dq->tail->next;
  }
  dq->size++;
}

int dequeue(DynamicQueue dq) {
  int ret;
  if(dq->head == dq->tail) {
    ret = dq->head->data;
    free(dq->head);
    dq->head = dq->tail = NULL;
  }
  else {
    Node tmp = dq->head;
    ret = tmp->data;
    dq->head = dq->head->next;
    dq->head->prev = NULL;
    free(tmp);
  }
  dq->size--;
  return ret;
}

void removeDynamicQueue(DynamicQueue dq) {
  Node tmp = NULL, iter = dq->head;
  while(iter) {
    tmp = iter;
    iter = iter->next;
    free(tmp);
  }
  free(dq);
  dq = NULL;
}

void printDynamicQueue(DynamicQueue dq) {
  printf("size: %d\n", dq->size);
  printf("[ ");
  Node iter = dq->head;
  while(iter) {
    printf("%d ", iter->data);
    iter = iter->next;
  }
  printf("]\n");
}

int testDynamicQueue() {
  DynamicQueue dq = newDynamicQueue();
  if(isEmptyDynamicQueue(dq)) printf("DynamicQueue is empty\n");
  else printf("DynamicQueue is not empty\n");

  for(int i = 1; i < 100; i++) {
    enqueue(dq, i);
    printf("enqueue(%d)\n", i);
  }

  if(isEmptyDynamicQueue(dq)) printf("DynamicQueue is empty\n");
  else printf("DynamicQueue is not empty\n");

  for(int i = 1; ; i++) {
    if(!isEmptyDynamicQueue(dq)) {
      printf("dequeue(): %d\n", dequeue(dq));  
    }
    else {
      printf("DynamicQueue is empty\n");
      break;
    }
  }
  removeDynamicQueue(dq);
  return 0;
}

int main() {
  testDynamicQueue();
  return 0;
}