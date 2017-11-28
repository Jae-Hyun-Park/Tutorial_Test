#include <stdio.h>

int data[10] = { 20, 1, 5, 3, 25, 4, 10, 22, 9, 11 };
int n = 1;

void swap(int*a, int*b) {
	int i = 0;

	int temp = *a;
	*a = *b;
	*b = temp;

	printf("%d차 정렬 : ", n);

	for (i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	n++;
	printf("\n====================\n");
}

void quick_sort(int* array, int left, int right) {
	int L = left, R = right;
	int mid = (left + right) / 2;
	int pivot = array[mid];

	while (L <= R) {
		while (array[L] <= pivot && L < R) {
			L++;
		}
		while (array[R] > pivot && L <= R) {
			R--;
		}
		if (L <= R) {
			if (L != R) {
				printf("현재 pivot = %d\n", pivot);
				swap(&array[L], &array[R]);
			}
			else if (L == R) {
				printf("현재 pivot = %d\n", pivot);
				swap(&array[L], &array[mid]);
			}
			L++;
			R--;
		}
	}
	if (left < R) {
		printf("pivot(%d)의 왼쪽 배열을 정렬\n", pivot);
		quick_sort(array, left, R);
	}
	if (L < right) {
		printf("pivot(%d)의 오른쪽 배열을 정렬\n", pivot);
		quick_sort(array, L, right);
	}
}

void main() {
	int i = 0;
	printf("기존 배열 : ");
	for (i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	printf("\n====================\n");
	quick_sort(data, 0, 9);
}
