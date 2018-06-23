#include <stdio.h>
#include <malloc.h>
 
int N;
int* arr;

void merge(int* src, int from, int mid, int to, int* dst) {
  int i = from, j = mid + 1;
  for(int k = from; k <= to; k++) {
    if(i > mid) dst[k] = src[j++];
    else if(j > to) dst[k] = src[i++];
    else if(src[j] < src[i]) dst[k] = src[j++];
    else dst[k] = src[i++];
  }
}

void _MergeSort(int* src, int from, int to, int* dst) {
  if(to <= from) return;
  int mid = (to + from) / 2;
  _MergeSort(dst, from, mid, src);
  _MergeSort(dst, mid + 1, to, src);
  if(src[mid] < src[mid + 1]) for(int i = from; i <= to; i++) dst[i] = src[i];
  merge(src, from, mid, to, dst);
}

void MergeSort(int* arr, int from, int to) {
  int* cpy = (int*)malloc(sizeof(int) * (to - from + 1));
  for(int i = 0; i < to - from + 1; i++) cpy[i] = arr[i];
  _MergeSort(cpy, from, to, arr);  
}

int main() {
  scanf("%d", &N);
  arr = (int*)malloc(sizeof(int) * N);
  for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
  MergeSort(arr, 0, N - 1);
  for (int i = 0; i < N; i++) printf("%d ", arr[i]);
  printf("\n");
  return 0;
}