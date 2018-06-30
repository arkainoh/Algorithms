#include <stdio.h>
#include <malloc.h>
#define VERTICES 10

int N;

typedef struct _weightedVertex* WeightedVertex;
typedef struct _weightedVertex {
  int n, weight;
  WeightedVertex next;
} weightedVertex;

typedef struct _weightedAdjacentVertexList {
  WeightedVertex adj[VERTICES + 1];
} weightedAdjacentVertexList;
typedef weightedAdjacentVertexList* WeightedAdjacentVertexList;

WeightedAdjacentVertexList newWeightedAdjacentVertexList() {
  WeightedAdjacentVertexList ret = (WeightedAdjacentVertexList)malloc(sizeof(weightedAdjacentVertexList));
  for(int i = 0; i <= VERTICES; i++) ret->adj[i] = NULL;
  return ret;
}

WeightedVertex newWeightedVertex(int n, int weight) {
  WeightedVertex ret = (WeightedVertex)malloc(sizeof(weightedVertex));
  ret->n = n;
  ret->weight = weight;
  ret->next = NULL;
  return ret;
}

void addEdge(WeightedAdjacentVertexList g, int from, int to, int weight) {
  if(!g->adj[from]) {
    g->adj[from] = newWeightedVertex(to, weight);
    return;
  }

  WeightedVertex iter = g->adj[from];
  while(iter->next) iter = iter->next;
  iter->next = newWeightedVertex(to, weight);
}

void removeWeightedAdjacentVertexList(WeightedAdjacentVertexList g) {
  WeightedVertex iter, tmp;
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

void printWeightedAdjacentVertexList(WeightedAdjacentVertexList g) {
  WeightedVertex iter;
  for(int i = 1; i <= N; i++) {
    iter = g->adj[i];
    printf("%d: ", i);
    while(iter) {
      printf("%d(%d) ", iter->n, iter->weight);
      iter = iter->next;
    }
    printf("\n");
  }
}

void testWeightedAdjacentVertexList() {
  N = 6;
  WeightedAdjacentVertexList g = newWeightedAdjacentVertexList();
  addEdge(g, 1, 2, 10);
  addEdge(g, 1, 3, 30);
  addEdge(g, 1, 4, 15);
  addEdge(g, 2, 5, 20);
  addEdge(g, 3, 6, 5);
  addEdge(g, 4, 3, 5);
  addEdge(g, 4, 6, 20);
  addEdge(g, 5, 6, 20);
  addEdge(g, 6, 4, 20);
  printWeightedAdjacentVertexList(g);
}

int main() {
  testWeightedAdjacentVertexList();
  return 0;
}