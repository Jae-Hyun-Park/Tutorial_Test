#include <stdio.h>

int data[10] = { 20, 1, 5, 3, 25, 4, 10, 22, 9, 11 };
int n = 1;

void swap(int*a, int*b) {
	int i = 0;

	int temp = *a;
	*a = *b;
	*b = temp;

	printf("%d�� ���� : ", n);

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
				printf("���� pivot = %d\n", pivot);
				swap(&array[L], &array[R]);
			}
			else if (L == R) {
				printf("���� pivot = %d\n", pivot);
				swap(&array[L], &array[mid]);
			}
			L++;
			R--;
		}
	}
	if (left < R) {
		printf("pivot(%d)�� ���� �迭�� ����\n", pivot);
		quick_sort(array, left, R);
	}
	if (L < right) {
		printf("pivot(%d)�� ������ �迭�� ����\n", pivot);
		quick_sort(array, L, right);
	}
}

void main() {
	int i = 0;
	printf("���� �迭 : ");
	for (i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	printf("\n====================\n");
	quick_sort(data, 0, 9);
}
