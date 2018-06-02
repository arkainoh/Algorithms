#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Shuffle(int* a, int N) {
	for(int i = N - 1; i > 0; i--) {
		int r = rand() % (i + 1);
		swap(&a[r], &a[i]);
	}
}

void testShuffle() {
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Shuffle(a, 10);
	for(int i = 0; i < 10; i++) printf("%d ", a[i]);
	printf("\n");
}

int main() {
	srand(time(NULL));
	testShuffle();
	return 0;
}