#include<stdio.h>
#include<stdlib.h>

struct Node{
    int val;
    Node *next;
};

Node *createLL(int *arr, int size){
    struct Node *temp = NULL;
    struct Node *prev = NULL;
    struct Node *head = NULL;
    for(int i=0; i<size; i++){
        temp = (Node *)malloc(sizeof(Node));
        if(prev==NULL)
            head = temp;
        else
            prev->next = temp;
        prev = temp;
        temp->val = i;
        temp->next = NULL;
    }
    return head;

}

void reverseLL(Node *head){
    Node *prev = NULL, *temp;
    Node *ptr = head;

    if(head == NULL || head->next == NULL)
        return ;
    
    prev = head;
    while(ptr!=NULL){
        temp = ptr;
        ptr->next = prev;
        prev = ptr;
        ptr = temp->next;
    }
}

void printLL(Node *head){
    struct Node *ptr = head;
    while(ptr!=NULL){
        printf("%d ",ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

int main(){
    Node *head = NULL;
    int arr[] = {1, 2, 3, 4, 5};
    head = createLL(arr, 5);
    printLL(head);
    reverseLL(head);
    printLL(head);
    printf("\n end of program!");
    return 0;

}