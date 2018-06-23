#include <stdio.h>

int Ceiling(int* arr, int from, int to, int target) {
  while(from <= to) {
    int mid = (from + to) / 2;
    if(arr[mid] > target) to = mid - 1;
    else from = mid + 1;
  }
  return from;
}

void testCeiling() {
  int a[10];
  for(int i = 0; i < 10; i++) printf("%2d ", i);
  printf("\n");
  for(int i = 0; i < 10; i++) {
    a[i] = i * 2;
    printf("%2d ", a[i]);
  }
  printf("\n");
  printf("Ceiling(%d): %d\n", -1, Ceiling(a, 0, 9, -1));
  printf("Ceiling(%d): %d\n", 0, Ceiling(a, 0, 9, 0));
  printf("Ceiling(%d): %d\n", 3, Ceiling(a, 0, 9, 3));
  printf("Ceiling(%d): %d\n", 7, Ceiling(a, 0, 9, 7));
  printf("Ceiling(%d): %d\n", 9, Ceiling(a, 0, 9, 9));
  printf("Ceiling(%d): %d\n", 10, Ceiling(a, 0, 9, 10));
  printf("Ceiling(%d): %d\n", 16, Ceiling(a, 0, 9, 16));
  printf("Ceiling(%d): %d\n", 18, Ceiling(a, 0, 9, 18));
  printf("Ceiling(%d): %d\n", 19, Ceiling(a, 0, 9, 19));
}

int main() {
  testCeiling();
}