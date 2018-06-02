#include <stdio.h>
#include <malloc.h>
#define NODES 10

typedef struct _node* Node;
typedef struct _node {
  int data;
  Node next;
} node;

typedef struct _linkedList {
  Node head;
  int size;
} linkedList;
typedef linkedList* LinkedList;

LinkedList newLinkedList() {
  LinkedList ret = (LinkedList)malloc(sizeof(linkedList));
  ret->head = NULL;
  ret->size = 0;
  return ret;
}

Node newNode(int data) {
  Node ret = (Node)malloc(sizeof(node));
  ret->data = data;
  ret->next = NULL;
  return ret;
}

void add(LinkedList ll, int data) {
  if(!ll->head) ll->head = newNode(data);
  else {
    Node iter = ll->head;
    while(iter->next) iter = iter->next;
    iter->next = newNode(data);
  }
  ll->size++;
}

Node rmv(LinkedList ll, int data) {
  if(!ll->head) return NULL;
  else if(ll->head->data == data) {
    Node ret = ll->head;
    ll->head = ret->next;
    ll->size--;
    return ret;
  }
  else {
    Node ret = NULL, iter = ll->head;
    while(iter->next) {
      if(iter->next->data == data) {
        ret = iter->next;
        iter->next = ret->next;
        ll->size--;
        break;
      }
      iter = iter->next;
    }
    return ret;
  }
}

Node search(LinkedList ll, int data) {
  if(!ll->head) return NULL;
  else {
    Node ret = NULL, iter = ll->head;
    while(iter) {
      if(iter->data == data) {
        ret = iter;
        break;
      }
      iter = iter->next;
    }
    return ret;
  }
}

void removeLinkedList(LinkedList ll) {
  Node tmp = NULL, iter = ll->head;
  while(iter) {
    tmp = iter;
    iter = iter->next;
    free(tmp);
  }
  free(ll);
  ll = NULL;
}

void printLinkedList(LinkedList ll) {
  printf("size: %d\n", ll->size);
  printf("[ ");
  Node iter = ll->head;
  while(iter) {
    printf("%d ", iter->data);
    iter = iter->next;
  }
  printf("]\n");
}

void testLinkedList() {
  LinkedList ll = newLinkedList();

  add(ll, 3);
  add(ll, 2);
  add(ll, 4);
  add(ll, 8);
  add(ll, 7);
  
  printLinkedList(ll);

  printf("rmv(%d)\n", 4);
  rmv(ll, 4);

  printLinkedList(ll);

  printf("search(%d): %d\n", 3, search(ll, 3)->data);
  Node n = search(ll, 4);
  printf("search(%d): ", 4);
  if(n) printf("%d\n", n->data);
  else printf("couldn't find %d\n", 4);

  removeLinkedList(ll);
}

int main() {
  testLinkedList();
  return 0;
}