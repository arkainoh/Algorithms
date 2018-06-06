#include <stdio.h>
 
int BinarySearch(int* arr, int from, int to, int target) {
    while (from <= to) {
        int mid = (from + to) / 2;
        if (arr[mid] > target) to = mid - 1;
        else if (arr[mid] < target) from = mid + 1;
        else return mid;
    }
    return -1;
}

void testBinarySearch() {
  int a[10];
  for(int i = 0; i < 10; i++) printf("%2d ", i);
  printf("\n");
  for(int i = 0; i < 10; i++) {
    a[i] = i * 2;
    printf("%2d ", a[i]);
  }
  printf("\n");
  printf("BinarySearch(%d): %d\n", -1, BinarySearch(a, 0, 9, -1));
  printf("BinarySearch(%d): %d\n", 0, BinarySearch(a, 0, 9, 0));
  printf("BinarySearch(%d): %d\n", 3, BinarySearch(a, 0, 9, 3));
  printf("BinarySearch(%d): %d\n", 7, BinarySearch(a, 0, 9, 7));
  printf("BinarySearch(%d): %d\n", 9, BinarySearch(a, 0, 9, 9));
  printf("BinarySearch(%d): %d\n", 10, BinarySearch(a, 0, 9, 10));
  printf("BinarySearch(%d): %d\n", 16, BinarySearch(a, 0, 9, 16));
  printf("BinarySearch(%d): %d\n", 18, BinarySearch(a, 0, 9, 18));
  printf("BinarySearch(%d): %d\n", 19, BinarySearch(a, 0, 9, 19));
}

int main() {
  testBinarySearch();
}