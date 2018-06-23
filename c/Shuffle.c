#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int* arr, int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void Shuffle(int* arr, int N) {
  for(int i = N - 1; i > 0; i--) {
    int r = rand() % (i + 1);
    swap(arr, r, i);
  }
}

void testShuffle() {
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Shuffle(arr, 10);
  for(int i = 0; i < 10; i++) printf("%d ", arr[i]);
  printf("\n");
}

int main() {
  srand(time(NULL));
  testShuffle();
  return 0;
}