#include <stdio.h>
 
int Floor(int* arr, int from, int to, int target) {
    while (from <= to) {
        int mid = (from + to) / 2;
        if (arr[mid] < target) from = mid + 1;
        else to = mid - 1;
    }
    return to;
}

void testFloor() {
  int a[10];
  for(int i = 0; i < 10; i++) printf("%2d ", i);
  printf("\n");
  for(int i = 0; i < 10; i++) {
    a[i] = i * 2;
    printf("%2d ", a[i]);
  }
  printf("\n");
  printf("Floor(%d): %d\n", -1, Floor(a, 0, 9, -1));
  printf("Floor(%d): %d\n", 0, Floor(a, 0, 9, 0));
  printf("Floor(%d): %d\n", 3, Floor(a, 0, 9, 3));
  printf("Floor(%d): %d\n", 7, Floor(a, 0, 9, 7));
  printf("Floor(%d): %d\n", 9, Floor(a, 0, 9, 9));
  printf("Floor(%d): %d\n", 10, Floor(a, 0, 9, 10));
  printf("Floor(%d): %d\n", 16, Floor(a, 0, 9, 16));
  printf("Floor(%d): %d\n", 18, Floor(a, 0, 9, 18));
  printf("Floor(%d): %d\n", 19, Floor(a, 0, 9, 19));
}

int main() {
    testFloor();
}