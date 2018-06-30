#include <stdio.h>
#include <malloc.h>
#define VERTICES 10

int N;

typedef struct _vertex* Vertex;
typedef struct _vertex {
  int n;
  Vertex next;
} vertex;

typedef struct _adjacentVertexList {
  Vertex adj[VERTICES + 1];
} adjacentVertexList;
typedef adjacentVertexList* AdjacentVertexList;

AdjacentVertexList newAdjacentVertexList() {
  AdjacentVertexList ret = (AdjacentVertexList)malloc(sizeof(adjacentVertexList));
  for(int i = 0; i <= VERTICES; i++) ret->adj[i] = NULL;
  return ret;
}

Vertex newVertex(int vertex) {
  Vertex ret = (Vertex)malloc(sizeof(vertex));
  ret->n = vertex;
  ret->next = NULL;
  return ret;
}

void addEdge(AdjacentVertexList g, int from, int to) {
  if(!g->adj[from]) {
    g->adj[from] = newVertex(to);
    return;
  }

  Vertex iter = g->adj[from];
  while(iter->next) iter = iter->next;
  iter->next = newVertex(to);
}

void removeAdjacentVertexList(AdjacentVertexList g) {
  Vertex iter, tmp;
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

void printAdjacentVertexList(AdjacentVertexList g) {
  Vertex iter;
  for(int i = 1; i <= N; i++) {
    iter = g->adj[i];
    printf("%d: ", i);
    while(iter) {
      printf("%d ", iter->n);
      iter = iter->next;
    }
    printf("\n");
  }
}

void testAdjacentVertexList() {
  N = 3;
  AdjacentVertexList g = newAdjacentVertexList();
  Vertex iter;
  addEdge(g, 3, 1);
  addEdge(g, 2, 4);
  addEdge(g, 1, 2);
  addEdge(g, 1, 6);
  printAdjacentVertexList(g);
}

int main() {
  testAdjacentVertexList();
  return 0;
}