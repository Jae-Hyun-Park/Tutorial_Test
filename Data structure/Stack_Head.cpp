#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
};

struct Node *top = NULL;
struct Node *stack = NULL;
int Count = -1;

void Interval() {
	printf("------------------------------------\n");
}

void Push(int x) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = x;
	temp->next = top;

	top = temp;
	Count++;
	return;
}

void Pop() {
	struct Node* temp;

	if (top == NULL) {
		printf("Err!\n");
		Interval();
		return;
	}

	temp = top;
	top = temp->next;
	free(temp);
	Count--;
	return;
}

void Top() {
	stack = top;

	if (top == NULL) {
		printf("현재 스택의 top은 %d번지에 있으며, 안에 들어있는 값은 없습니다.\n", top);
		Interval();
		return;
	}

	printf("현재 스택의 TOP은 %d번지에 있으며, 안에 들어있는 값은 %d 입니다.\n", Count, stack->data);
	Interval();
	return;
}

void Print() {
	stack = top;

	while (stack != NULL) {
		printf("%d\n", stack->data);
		stack = stack->next;
	}

	Interval();
	return;
}

void isEmpty() {
	stack = top;

	if (top == NULL) {
		printf("현재 스택은 비어있는 상태입니다.\n");
		Interval();
		return;
	}

	printf("현재 스택은 비어있지 않으며, %d개의 데이터가 들어있습니다.\n", Count + 1);
	Interval();
	return;
}

void main() {
	int s, x = 0;

	while (1)
	{
		printf("번호를 선택하여 주십시오.\n 1: PUSH\n 2. POP\n 3. TOP\n 4. ISEmpty\n 5. EXIT\n");
		scanf("%d", &s);
		Interval();

		switch (s) {

		case 1:
			printf("입력할 데이터를 적어주십시오.\n");
			scanf("%d", &x);
			Interval();
			Push(x);
			Print();
			break;

		case 2:
			Pop();
			Print();
			break;

		case 3:
			Top();
			break;

		case 4:
			isEmpty();
			break;

		case 5:
			return;

		default:
			printf("값을 잘못 입력하였습니다! 다시입력해주십시오\n");
			Interval();
			break;
		}
	}
}
