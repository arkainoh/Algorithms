#include <stdio.h>
#include <malloc.h>
#define VERTICES 10

int N;

typedef struct _weightedEdge* WeightedEdge;
typedef struct _weightedEdge {
  int from, to, weight;
  WeightedEdge next;
} weightedEdge;

typedef struct _weightedAdjacentEdgeList {
  WeightedEdge adj[VERTICES + 1];
} weightedAdjacentEdgeList;
typedef weightedAdjacentEdgeList* WeightedAdjacentEdgeList;

WeightedAdjacentEdgeList newWeightedAdjacentEdgeList() {
  WeightedAdjacentEdgeList ret = (WeightedAdjacentEdgeList)malloc(sizeof(weightedAdjacentEdgeList));
  for(int i = 0; i <= VERTICES; i++) ret->adj[i] = NULL;
  return ret;
}

WeightedEdge newWeightedEdge(int from, int to, int weight) {
  WeightedEdge ret = (WeightedEdge)malloc(sizeof(weightedEdge));
  ret->from = from;
  ret->to = to;
  ret->weight = weight;
  ret->next = NULL;
  return ret;
}

void addEdge(WeightedAdjacentEdgeList g, int from, int to, int weight) {
  if(!g->adj[from]) {
    g->adj[from] = newWeightedEdge(from, to, weight);
    return;
  }

  WeightedEdge iter = g->adj[from];
  while(iter->next) iter = iter->next;
  iter->next = newWeightedEdge(from, to, weight);
}

void removeWeightedAdjacentEdgeList(WeightedAdjacentEdgeList g) {
  WeightedEdge iter, tmp;
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

void printWeightedAdjacentEdgeList(WeightedAdjacentEdgeList g) {
  WeightedEdge iter;
  for(int i = 1; i <= N; i++) {
    iter = g->adj[i];
    printf("%d: ", iter->from);
    while(iter) {
      printf("%d(%d) ", iter->to, iter->weight);
      iter = iter->next;
    }
    printf("\n");
  }
}

void testWeightedAdjacentEdgeList() {
  N = 6;
  WeightedAdjacentEdgeList g = newWeightedAdjacentEdgeList();
  addEdge(g, 1, 2, 10);
  addEdge(g, 1, 3, 30);
  addEdge(g, 1, 4, 15);
  addEdge(g, 2, 5, 20);
  addEdge(g, 3, 6, 5);
  addEdge(g, 4, 3, 5);
  addEdge(g, 4, 6, 20);
  addEdge(g, 5, 6, 20);
  addEdge(g, 6, 4, 20);
  printWeightedAdjacentEdgeList(g);
}

int main() {
  testWeightedAdjacentEdgeList();
  return 0;
}