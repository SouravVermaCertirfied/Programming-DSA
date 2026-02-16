/*
 Implement circular queue
    - should have following operatoins:
        - insert (inserts rear , overwrites if queue is full)
        - delete ( delete front )
        - pop ( reads front )
    - use structutre
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define QSIZE 10

typedef struct{
    int *cq;
    int front;
    int rear;
} circularQ;

void initQ(circularQ *mycq){
    mycq->front = -1;
    mycq->rear = -1;
    mycq->cq = (int *)calloc(QSIZE, sizeof(int));
}

void insert(circularQ *mycq, int val){
    if(mycq->front == -1 && mycq->rear == -1){
        mycq->front += 1;
        mycq->rear += 1;
    }
    else{
        mycq->rear = (mycq->rear + 1) % QSIZE;
    }
    mycq->cq[mycq->rear] = val;
}

void pop(circularQ *mycq){
    if(mycq->front == -1){
        printf("Q is empty \n");
    }
    else{
        printf("%d ",mycq->cq[mycq->front]);
    }
}

void delete(circularQ *mycq){
    if(mycq->rear == -1){
        printf("Q is already empty, cannot delete \n");
    }
    else{
        if(mycq->rear == mycq->front){ // only one item in the queue
            mycq->front = -1; 
        }
        mycq->rear -= 1;
    }
}

void printmycq(circularQ *mycq){
    if(mycq->front == -1){
        printf("Q is empty \n");
    }
    printf("Printing the values : \n");
    if(mycq->front <= mycq->rear){
        int i = mycq->front;
        while(mycq->front<= mycq->rear){
            printf("%d ",mycq->cq[i]);
        }
    }
    else{
        int i =  mycq->front;
        while(i<QSIZE){
            print("%d ",mycq->cq[i]);
        }
        i = 0;
        while(i<=mycq->rear){
            print("%d ",mycq->cq[i]);
        }
    }
    printf("\n");
}



int main(){
    circularQ mycq;
    initQ(&mycq);
    if(mycq.cq == NULL)
        return 1;  // end program memory could not be allocated
    
    for( int i=0; i<15; i++){
        insert(&mycq, i);
    }
    printf(&mycq);
    pop(&mycq);
    delete(&mycq);
    printf(&mycq);
    getch();
}