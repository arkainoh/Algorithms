#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int N;
int* arr;

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void Shuffle(int* arr, int from, int to) {
  for(int i = to; i > from; i--) {
    int r = rand() % (i + 1);
    swap(arr, r, i);
  }
}

int partition(int* arr, int from, int to) {
  int i = from, j = to + 1;
  while(1) {
    while(arr[++i] < arr[from]) if(i == to) break;
    while(arr[from] < arr[--j]);
    if(i >= j) break;
    swap(arr, i, j);
  }
  swap(arr, from, j);
  return j;
}

int QuickSearch(int* arr, int k, int from, int to) {
  Shuffle(arr, from, to);
  while(to > from) {
    int j = partition(arr, from, to);
    if(j < k) from = j + 1;
    else if(j > k) to = j - 1;
    else return arr[k];
  }
  return arr[k];
}

int main() {
  srand(time(NULL));
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  for(int i = 0; i < N; i++) scanf("%d", &arr[i]);
  for(int i = 0; i < N; i++) printf("QuickSearch(%d): %d\n", i, QuickSearch(arr, i, 0, N - 1));
  return 0;
}