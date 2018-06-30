#include <stdio.h>
#include <malloc.h>
#define VERTICES 10

int N;

typedef struct _edge* Edge;
typedef struct _edge {
  int from, to;
  Edge next;
} edge;

typedef struct _adjacentEdgeList {
  Edge adj[VERTICES + 1];
} adjacentEdgeList;
typedef adjacentEdgeList* AdjacentEdgeList;

AdjacentEdgeList newAdjacentEdgeList() {
  AdjacentEdgeList ret = (AdjacentEdgeList)malloc(sizeof(adjacentEdgeList));
  for(int i = 0; i <= VERTICES; i++) ret->adj[i] = NULL;
  return ret;
}

Edge newEdge(int from, int to) {
  Edge ret = (Edge)malloc(sizeof(edge));
  ret->from = from;
  ret->to = to;
  ret->next = NULL;
  return ret;
}

void addEdge(AdjacentEdgeList g, int from, int to) {
  if(!g->adj[from]) {
    g->adj[from] = newEdge(from, to);
    return;
  }

  Edge iter = g->adj[from];
  while(iter->next) iter = iter->next;
  iter->next = newEdge(from, to);
}

void removeAdjacentEdgeList(AdjacentEdgeList g) {
  Edge iter, tmp;
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

void printAdjacentEdgeList(AdjacentEdgeList g) {
  Edge iter;
  for(int i = 1; i <= N; i++) {
    iter = g->adj[i];
    printf("%d: ", iter->from);
    while(iter) {
      printf("%d ", iter->to);
      iter = iter->next;
    }
    printf("\n");
  }
}

void testAdjacentEdgeList() {
  N = 3;
  AdjacentEdgeList g = newAdjacentEdgeList();
  Edge iter;
  addEdge(g, 3, 1);
  addEdge(g, 2, 4);
  addEdge(g, 1, 2);
  addEdge(g, 1, 6);
  printAdjacentEdgeList(g);
}

int main() {
  testAdjacentEdgeList();
  return 0;
}