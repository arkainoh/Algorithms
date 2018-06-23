#include <stdio.h>
#include <malloc.h>
 
int N;
int* arr;

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
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

void QuickSort(int* arr, int from, int to) {
  if(to <= from) return;
    int pivot = partition(arr, from, to);
    QuickSort(arr, from, pivot - 1);
    QuickSort(arr, pivot + 1, to);
}
 
int main() {
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
  QuickSort(arr, 0, N - 1);
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  printf("\n");
  return 0;
}