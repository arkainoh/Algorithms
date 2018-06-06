#include <stdio.h>
#include <malloc.h>
 
int N;
int* arr;
int* cpy;
void MergeSort(int* arr, int from, int to, int* cpy) {
  if (from + 1 == to) {
    arr[from] = cpy[from];
    return;
  }
  int mid = (from + to) / 2;
  MergeSort(cpy, from, mid, arr);
  MergeSort(cpy, mid, to, arr);
 
  int i = from, j = mid, k = from;
  while (i < mid && j < to) {
    if (cpy[i] < cpy[j]) arr[k++] = cpy[i++];
    else arr[k++] = cpy[j++];
  }
  while (i < mid) arr[k++] = cpy[i++];
  while (j < to) arr[k++] = cpy[j++];
}
 
int main() {
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  cpy = (int*)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &arr[i]);
    cpy[i] = arr[i];
  }
  MergeSort(arr, 0, N, cpy);
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  printf("\n");
  return 0;
}