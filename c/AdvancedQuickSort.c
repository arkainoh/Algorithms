#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define THETA 7
 
int N;
int* arr;

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void InsertionSort(int* arr, int from, int to) {
  for(int i = from + 1; i <= to; i++)
    for(int j = i; j > from && arr[j] < arr[j - 1]; j--)
      swap(arr, j, j - 1);
}

void Shuffle(int* arr, int from, int to) {
  for(int i = to; i > from; i--) {
    int r = rand() % (i + 1);
    swap(arr, r, i);
  }
}

void _AdvancedQuickSort(int* arr, int from, int to) {
  if(to <= from + THETA) {
    InsertionSort(arr, from, to);
    return;
  }
  int lt = from, gt = to;
  int v = arr[from];
  int i = from;
  while(i <= gt) {
    if(arr[i] < v) swap(arr, lt++, i++);
    else if(arr[i] > v) swap(arr, i, gt--);
    else i++;
  }
  _AdvancedQuickSort(arr, from, lt - 1);
  _AdvancedQuickSort(arr, gt + 1, to);
}

void AdvancedQuickSort(int* arr, int from, int to) {
  Shuffle(arr, from, to);
  _AdvancedQuickSort(arr, from, to);
}
 
int main() {
  srand(time(NULL));
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
  AdvancedQuickSort(arr, 0, N - 1);
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  printf("\n");
  return 0;
}