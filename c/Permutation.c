#include <stdio.h>
#define SIZE 10

int N;
int permutation[SIZE + 1];
int number[SIZE + 1];

void printPermutation() {
  for(int i = 1; i <= N; i++) printf("%d ", permutation[i]);
  printf("\n");
}

void Permutation(int n) {
  if(n > N) {
    printPermutation();
    return;
  }

  for(int i = 1; i <= N; i++) {
    if(!number[i]) {
      number[i] = 1;
      permutation[n] = i;
      Permutation(n + 1);
      permutation[n] = 0;
      number[i] = 0;
    }
  }
}

void testPermutation() {
  N = 4;
  Permutation(1);
}

int main() {
  testPermutation();
  return 0;
}