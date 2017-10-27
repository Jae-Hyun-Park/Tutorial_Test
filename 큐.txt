#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;
struct Node *queue = NULL;
int Count = 0;

void Interval() {
	printf("------------------------------------\n");
}

void EnQueue(int x) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = x;
	temp->next = NULL;

	if (front == NULL) {
		front = rear = temp;
		Count++;
		return;
	}

	rear->next = temp;
	rear = temp;
	Count++;
	return;
}

void DeQueue() {
	struct Node* temp;

	if (front == NULL) {
		printf("Err!\n");
		Interval();
		return;
	}

	temp = front;
	front = temp->next;
	free(temp);
	Count--;
	return;
}

void Print() {
	queue = front;

	while (queue != NULL) {
		printf("%d\n", queue->data);
		queue = queue->next;
	}

	Interval();
	return;
}

void isEmpty() {
	queue = front;

	if (front == NULL) {
		printf("현재 큐는 비어있는 상태입니다.\n");
		Interval();
		return;
	}

	printf("현재 큐는 비어있지 않으며, %d개의 데이터가 들어있습니다.\n", Count);
	Interval();
	return;
}

void main() {
	int s, x = 0;

	while (1)
	{
		printf("번호를 선택하여 주십시오.\n 1: EnQueue\n 2. DeQueue\n 3. ISEmpty\n 4. EXIT\n");
		scanf("%d", &s);
		Interval();

		switch (s) {

		case 1:
			printf("입력할 데이터를 적어주십시오.\n");
			scanf("%d", &x);
			Interval();
			EnQueue(x);
			Print();
			break;

		case 2:
			DeQueue();
			Print();
			break;

		case 3:
			isEmpty();
			break;

		case 4:
			return;

		default:
			printf("값을 잘못 입력하였습니다! 다시입력해주십시오\n");
			Interval();
			break;
		}
	}
}
