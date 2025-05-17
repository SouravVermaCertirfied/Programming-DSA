// C++ program for implementation of FCFS
// scheduling
#include<iostream>
using namespace std;

class Node{
public:
	int val;
	Node *next;
	Node(int val){
		this->val = val;
		this->next = NULL;
	}
	Node(int val, Node* next){
		this->val = val;
		this->next = next;
	}

};

Node *createLL(int n){
	Node * head = NULL;
	Node * lastCreated = NULL;
	for(int i=0;i<n;i++){
		Node * temp = new Node(i);
		if(i == 0){
			head = temp;
			lastCreated = temp;
		}
		else{
			lastCreated->next = temp;
			lastCreated = temp;
		}

	}
	return head;
}

Node * insertAtBeginLL(Node* head, int val){
	Node * temp = new Node(val);
	if(head == NULL)
			return temp;
	temp->next = head;
	head = temp;
	return head;
}

Node * insertAtEnd(Node * head, int val){
	Node * temp = new Node(val);
	if(head == NULL)
		return temp;
	Node *ptr = head;
	while(ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = temp;
	return head;
}

void printLL(Node *head){
	Node * ptr = head;
	while(ptr!=NULL){
		cout<<ptr->val<<" ";
		ptr = ptr->next;
	}
	cout<<endl;
}

Node *insertAtPos(Node *head, int val, int pos){
	Node * temp = new Node(val);
	if(head == NULL)
		return temp;
	Node *ptr = head;
	int cnt = 0;
	while(ptr!=NULL){
		if(cnt == pos)
			break;
		else{
			ptr = ptr->next;
		}
		cnt++;
	}
	if(ptr==NULL)
		cout<<"Pos out of range!"<<endl;
	else{
		temp->next = ptr->next;
		ptr->next = temp;
	}
	return head;

}

Node *reverseLL(Node *head, int val){
	if(head == NULL || head->next==NULL)
		return head;
	Node *temp 	= NULL;
	Node *last 	= NULL;
	Node *ptr 	= head;
	while(ptr!=NULL){
		temp = ptr->next;
		ptr->next = last;
		last = ptr;
		ptr = temp;
	}
	
	return last;
}

int main(){
	Node * head = createLL(10);
	printLL(head);
	head = insertAtBeginLL(head, -1);
	printLL(head);
	head = insertAtEnd(head, 10);
	printLL(head);
	head = insertAtPos(head, 99, 11);
	printLL(head);
	return 0;
}
