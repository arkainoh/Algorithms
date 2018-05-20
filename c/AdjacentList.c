#include <stdio.h>
#include <malloc.h>
#define VERTICES 10

typedef struct _node* Node;
typedef struct _node {
  int vertex;
  Node next;
} node;

typedef struct _adjacentList {
  Node adj[VERTICES + 1];
} adjacentList;

typedef adjacentList* AdjacentList;

AdjacentList newAdjacentList() {
  AdjacentList ret = (AdjacentList)malloc(sizeof(adjacentList));
  for(int i = 0; i <= VERTICES; i++) ret->adj[i] = NULL;
  return ret;
}

Node newNode(int vertex) {
  Node ret = (Node)malloc(sizeof(node));
  ret->vertex = vertex;
  ret->next = NULL;
  return ret;
}

void addEdge(AdjacentList g, int from, int to) {
  if(!g->adj[from]) {
    g->adj[from] = newNode(to);
    return;
  }

  Node iter = g->adj[from];
  while(iter->next) iter = iter->next;
  iter->next = newNode(to);
}

void removeAdjacentList(AdjacentList g) {
  Node iter, tmp;
  for(int i = 0; i <= VERTICES; i++) {
    iter = g->adj[i];
    while(iter) {
      tmp = iter;
      iter = iter->next;
      free(tmp);
    }
  }

  free(g);
  g = NULL;
}

void testAdjacentList() {
  AdjacentList g = newAdjacentList();
  Node iter;
  addEdge(g, 3, 1);
  addEdge(g, 2, 4);
  addEdge(g, 1, 2);
  addEdge(g, 1, 6);
  for(int i = 1; i <= VERTICES; i++) {
    iter = g->adj[i];
    printf("%d: ", i);
    while(iter) {
      printf("%d ", iter->vertex);
      iter = iter->next;
    }
    printf("\n");
  }
}

int main() {
  testAdjacentList();
  return 0;
}