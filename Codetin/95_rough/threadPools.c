#include<stdio.h>
#include<pthread.h>

typedef struct tNode{
    int a;
    int b;
    struct tNode *next;

}tNode;

tNode* createNode(int a, int b, tNode *next){
    tNode *ptr = (tNode *)malloc(sizeof(tNode));
    ptr->a = a;
    ptr->b = b;
    ptr->next = next;
    return ptr;
}

typedef struct tqueue{
    tNode *head;
    tNode *tail;
}tqueue;


void enqNode(tqueue *tq, tNode *newNode){
    if(tq->tail==NULL){
        tq->head = newNode;
        tq->tail = newNode;
    }
    else{
        tq->tail->next = newNode;
        tq->tail = newNode;
    }
}

void deqNode(tqueue *tq){
    if()
}



void *worker(void *args){
    while(1){

    }
}

int main(){

    // init the queue
    tqueue jobqueue;
    jobqueue.head = NULL;
    jobqueue.tail = NULL;

    //fill the values in the queue
    for(int i=0; i<10; i++){

    }
    return 0;
}