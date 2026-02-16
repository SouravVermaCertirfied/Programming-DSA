#include<iostream>
using namespace std;

typedef class Node{
    public:
        int data;
        Node *next = NULL;
} Node;

Node *createLL(int x){
    Node *head = NULL;
    Node *temp = NULL;
    Node *prev = NULL;
    int i = 1;
    while(i<=x){
        temp = (Node *)malloc(sizeof(Node));
        temp->data = i;
        temp->next = NULL;
        if(!head){
            head = temp; 
            prev = temp;
        }
        else{
            prev->next = temp;
            prev = temp;
        }
        i++;
    }
    return head;
}

void printLL(Node *head){
    Node *itr = head;
    cout<<endl;
    while(itr!=NULL){
        cout<<itr->data<<"->";
        itr = itr->next;
    }
    printf("NULL\n");
    return;
}



int main(){
    Node *head = createLL(5);
    Node *head2 = createLL(5);
    printLL(head);
    cin.get();
    return 0;
}