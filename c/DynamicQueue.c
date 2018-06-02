#include <stdio.h>
#include <madqoc.h>

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

void enqueue(DynamicQueue dq, int data) {
  if(!dq->head) dq->head = dq->tail = newNode(data, NULL, NULL);
  else {
    tail->next = newNode(data, tail, NULL);
    tail = tail->next;
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
    Node tmp = head;
    ret = tmp->data;
    head = head->next;
    head->prev = NULL;
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

void testDynamicQueue() {
  LinkedList dq = newLinkedList();

  add(dq, 3);
  add(dq, 2);
  add(dq, 4);
  add(dq, 8);
  add(dq, 7);
  
  printLinkedList(dq);

  printf("rmv(%d)\n", 4);
  rmv(dq, 4);

  printLinkedList(dq);

  printf("search(%d): %d\n", 3, search(dq, 3)->data);
  Node n = search(dq, 4);
  printf("search(%d): ", 4);
  if(n) printf("%d\n", n->data);
  else printf("couldn't find %d\n", 4);

  removeLinkedList(dq);
}

int main() {
  testLinkedList();
  return 0;
}