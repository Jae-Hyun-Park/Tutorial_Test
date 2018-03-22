#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
};

struct Node * GetNewNode(int x) {

	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;
}

struct Node *Head = NULL;
struct Node *Tail = NULL;
struct Node *Linkedlist = NULL;

void InsertAtTail(int x) {
	Node *newNode = GetNewNode(x);
	if (Head == NULL) {
		Head = Tail = newNode;
		return;
	}
	Tail->next = newNode;
	newNode->prev = Tail;
	Tail = newNode;
}

void DeleteTail() {
	Node *temp;
	Linkedlist = Head;
	if (Head == NULL) {
		printf("Err!\n");
		return;
	}
	else if (Head == Tail) {
		Head = Tail = NULL;
		return;
	}
	
	while (Linkedlist->next->next != NULL) {
		Linkedlist = Linkedlist->next;
	}
	temp = Linkedlist->next;
	Linkedlist->next = temp->next;
	Tail = Linkedlist;
	free(temp);
	return;
}
void Print() {
	Linkedlist = Head;

	while (Linkedlist != NULL) {
		printf("%d ", Linkedlist->data);
		Linkedlist = Linkedlist->next;
	}

	printf("\n");
	return;
}

void main() {
	InsertAtTail(5);
	InsertAtTail(4);
	InsertAtTail(3);
	InsertAtTail(2);
	Print();
	DeleteTail();
	DeleteTail();
	DeleteTail();
	Print();
}
