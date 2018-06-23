#include <stdio.h>
#include <malloc.h>
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

void merge(int* src, int from, int mid, int to, int* dst) {
  int i = from, j = mid + 1;
  for(int k = from; k <= to; k++) {
    if(i > mid) dst[k] = src[j++];
    else if(j > to) dst[k] = src[i++];
    else if(src[j] < src[i]) dst[k] = src[j++];
    else dst[k] = src[i++];
  }
}

void _AdvancedMergeSort(int* src, int from, int to, int* dst) {
  if(to <= from + THETA) {
    InsertionSort(dst, from, to);
    return;
  }
  int mid = (to + from) / 2;
  _AdvancedMergeSort(dst, from, mid, src);
  _AdvancedMergeSort(dst, mid + 1, to, src);
  if(src[mid] < src[mid + 1]) {
    for(int i = from; i <= to; i++) dst[i] = src[i];
    return;
  }
  merge(src, from, mid, to, dst);
}

void AdvancedMergeSort(int* arr, int from, int to) {
  int* cpy = (int*)malloc(sizeof(int) * (to - from + 1));
  for(int i = 0; i < to - from + 1; i++) cpy[i] = arr[i];
  _AdvancedMergeSort(cpy, from, to, arr);  
}

int main() {
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  for(int i = 0; i < N; i++) scanf("%d", &arr[i]);
  AdvancedMergeSort(arr, 0, N - 1);
  for(int i = 0; i < N; i++) printf("%d ", arr[i]);
  printf("\n");
  return 0;
}