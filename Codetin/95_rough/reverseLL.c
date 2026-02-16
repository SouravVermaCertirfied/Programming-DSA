/*
    make a linked list
    print it
    reverse it
    
*/

#include<stdio.h> // for printf
#include<conio.h> // for getch
#include<stdlib.h> // for malloc


typedef struct _Node{
    int val;
    struct _Node *next;
} Node;

void addNode(Node **head, int val){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->next = NULL;
    temp->val = val;
    if(*head == NULL){
        *head = temp;
    }
    else{
        Node *ptr = *head;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

void printLL(Node *head){
    Node *ptr = head;
    while(ptr){
        printf("%d->",ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

Node *findMiddle(Node **head){
    /*
    if there is are none, return null
    if there is just one then return the first element
    otherwise let the faster run at twice the speed of slower 
    */
    if(*head == NULL)
        return NULL;
    Node *fast = *head;
    Node *slow = *head;
    int flag = 1;
    while(fast->next != NULL){
        if(flag){
            flag = 0;
        }
        else{
            flag = 1;
            slow = slow->next;
        }
        fast = fast->next;
    }
    printf("The midde vlaue is : %d \n", slow->val);
    return slow;
    

}

Node *reverseLL(Node *head){
    Node *ptr = head;
    Node *last = NULL;
    Node *temp = NULL;
    while(ptr){
        temp = ptr->next;
        ptr->next = last;
        last = ptr;
        ptr = temp;
    }
    return last;
}

int main(){
    Node *head = NULL;
    for(int i=1; i<=2; i++){
        addNode(&head, i);
    }
    printLL(head);
    head = reverseLL(head);
    printLL(head);
    Node *middle = findMiddle(&head);
    printf("\n the middle value is", middle->val);
    getch();
    return 0;
}