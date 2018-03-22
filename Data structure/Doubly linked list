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

void InsertAtHead(int x) {
	Node *newNode = GetNewNode(x);
	if (Head == NULL) {
		Head = Tail = newNode;
		return;
	}
	Head->prev = newNode;
	newNode->next = Head;
	Head = newNode;
}

void DeleteHead() {
	Node *temp;

	if (Head == NULL) {
		printf("Err!\n");
		return;
	}

	temp = Head;
	Head = temp->next;
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
	InsertAtHead(5);
	InsertAtHead(4);
	InsertAtHead(3);
	InsertAtHead(2);
	Print();
	DeleteHead();
	DeleteHead();
	DeleteHead();
	Print();
}
