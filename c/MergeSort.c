#include <stdio.h>
#include <malloc.h>
 
int N;
int* arr;
int* cpy;
void MergeSort(int* arr, int start, int length, int* cpy) {
  if (start + 1 == length) {
    arr[start] = cpy[start];
    return;
  }
  int mid = (start + length) / 2;
  MergeSort(cpy, start, mid, arr);
  MergeSort(cpy, mid, length, arr);
 
  int i = start, j = mid, k = start;
  while (i < mid && j < length) {
    if (cpy[i] < cpy[j]) arr[k++] = cpy[i++];
    else arr[k++] = cpy[j++];
  }
  while (i < mid) arr[k++] = cpy[i++];
  while (j < length) arr[k++] = cpy[j++];
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