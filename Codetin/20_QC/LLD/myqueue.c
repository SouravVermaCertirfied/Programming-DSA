/*
create a DS Queue
    - should enque - add element
    - should dequeue - remove oldest element
    - print all elements in order
*/
#include<stdio.h>

typedef struct{
    int front;
    int rear;
    int capacity;
    int data[10];
}que;

void enque(que *q, int x){
    if(q->rear+1 == q->capacity)
        return;
    
    q->rear += 1;
    q->data[q->rear] = x;
    if(q->front==-1)
        q->front += 1;
    
    return;
}

void deque(que *q){
    if(q->front==-1 && q->rear==-1)
        return;
    
    if(q->front==q->rear){
        q->rear = -1;
        q->front = -1;
    }
    else if(q->front<q->rear)
        q->front += 1;
    return;
}

void printall(que *q){
    printf("Printing the q in order now \n");
    if(q->front==-1 && q->rear==-1){
        printf("empty q \n");
        return ;
    }
        
    for(int i=q->front; i<=q->rear;i++){
        printf("%d",q->data[i]);
    }
    printf("\n");
}

void printer(que *q){
    printf("These are the meta data : %d %d %d\n",q->front, q->rear, q->capacity);
    return;
}

int main(){
    que q = {-1,-1,10};
    printer(&q);
    int arr[6] = {0, 1, 2, 3, 4, 5};
    for(int i=0;i<6;i++){
        enque(&q, arr[i]);
        printer(&q);
    }
    printall(&q);
    printf("Now dequeue \n");
    for(int i=0;i<6;i++){
        // enque(&q, arr[i]);
        deque(&q);
        printer(&q);
        // printall(&q);
    }
    printall(&q);
    printer(&q);
    // printf("Hello all");
    return 0;
}