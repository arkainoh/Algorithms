#include <stdio.h>
#include <malloc.h>

int N;
int *arr;

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

int main() {
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
  InsertionSort(arr, 0, N - 1);
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  printf("\n");
  return 0;
}