#include <stdio.h>

int A[10];
int front = -1;
int rear = -1;

bool IsEmpty() {
	if (front == -1 && rear == -1) {
		return true;
	}
	else
		return false;
}

void Enqueue(int x) {
	if ((rear+1)%10 == front) {
		printf("queue is full!");
		return;
	}
	else if (IsEmpty() == true) {
		front = rear = 0;
	}
	else {
		rear = (rear+1)%10;
	}
	A[rear] = x;

	return;
}

void Dequeue() {
	if (IsEmpty() == true) {
		printf("queue is Empty!");
		return;
	}
	else if (front == rear) {
		front = rear = -1;
	}
	else {
		A[front] = NULL;
		front = (front + 1) % 10;
	}
}

void Print() {

	for (int i = 0; i < 10; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	printf("front = %d, °ª = %d \n", front, A[front]);
	printf("rear = %d, °ª = %d \n", rear, A[rear]);
}
void main() {

	Enqueue(2);
	Enqueue(5);
	Enqueue(7);
	Dequeue();
	Enqueue(3);
	Enqueue(1);
	Enqueue(9);
	Enqueue(10);
	Enqueue(4);
	Enqueue(6);
	Dequeue();
	Enqueue(2);
	Enqueue(15);
	Dequeue();

	Print();

	return;
}
