//============================================================================
// Name        : base.cpp
// Author      : osv1cob
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

typedef struct doubelinkedlist {
	int data;
	struct doubelinkedlist * next;
	struct doubelinkedlist * prev;
} node;


node * createDoubleLinkedList(node * head, int numberOfNodes){
	node *temp, *lastnode;

	for(int i =0; i<numberOfNodes; i++){
		if(i==0){
			temp =  (node *)malloc(sizeof(node));
			head = temp;
			temp->data = i;
			temp->next = NULL;
			temp->prev = NULL;
			lastnode = temp;
		}
		else{
			temp =  (node *)malloc(sizeof(node));
			temp->data = i;
			temp->next = NULL;
			temp->prev = lastnode;
			lastnode->next= temp;
			lastnode = temp;
		}
	}
	return head;
}

void printAllNodes(node * head){
	if(head == NULL){
		printf("List is empty.");
	}
	else{
		node * loc = head;
		while(loc!=NULL){
			printf("\nData: %d \t Prev: 0x%p \t Next: 0x%p \t Curr: 0x%p", loc->data, loc->prev, loc->next, loc);
			loc = loc->next;
		}
	}
}

int main() {
	int numberOfNodes;
	node * head = NULL;
	//printf("Enter a number : "); fflush(stdout);
	//scanf("%d", &numberOfNodes);
	numberOfNodes = 100;
	printf("The number of nodes to be created are : %d\n", numberOfNodes);

	head = createDoubleLinkedList(head, numberOfNodes);
	printAllNodes(head); //no more

	printf("\n\n********Program ends**********");
	return 0;
}

