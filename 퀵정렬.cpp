#include <stdio.h>

void swap(int*a, int*b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int* array, int left, int right) {
	int L = left, R = right;
	int mid = (left + right) / 2;
	int pivot = array[mid];

	while (L <= R) {
		while (array[L] < pivot) {
			L++;
		}
		while(array[R] > pivot) {
			R--;
		}
		if (L <= R) {
			if (L != R) {
				swap(&array[L], &array[R]);
			}
			else if (L == R) {
				swap(&array[L], &array[mid]);
			}
			L++;
			R--;
		}
	}
	if (left < R) {
		quick_sort(array, left, R);
	}
	if (L < right) {
		quick_sort(array, L, right);
	}
}

void main() {
	int data[10] = { 20, 1, 5, 3, 25, 4, 10, 22, 9, 11 };
	int i = 0;
	quick_sort(data, 0, 9);
	for (i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
}
