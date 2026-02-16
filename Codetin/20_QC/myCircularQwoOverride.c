/*
3. Medium – Circular Buffer without Overwrite
Question:
    Design a circular buffer without overwrite support.
    When the buffer is full and a new element cannot be enqued.
Operations:
    enqueue(x) – overwrite if full
    dequeue() – remove the oldest element
    getAll() – return current contents in order
Goal: 
    
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int capacity;
    int front;
    int rear;
    int *data;
} cqueue;

cqueue *qinit(int c, int f, int r){
    cqueue *q = (cqueue *)malloc(sizeof(cqueue));
    q->capacity = c;
    q->front = f ;
    q->rear = r;
    int *d = (int*)calloc(c, sizeof(int));
    q->data = d;
    return q;
}

void freeq(cqueue *q){
    free(q->data);
    q->data = NULL;
    free(q);
    q = NULL;
    return;
}

char qfull(cqueue *q){
    if(((q->rear+1) % q->capacity) == q->front)
        return 1;
    return 0;
}

char empty(cqueue *q){
    if(q->rear == -1 && q->front == -1)
        return 1;
    return 0;
}

void enq(cqueue *q, int x){
    if(qfull(q)){
        printf("Queue is full, abort. \n");
        return;
    }
    if(q->front==-1)
        q->front = (q->front + 1) % q->capacity;
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = x;
    return;
}

void deque(cqueue *q){
    if(empty(q)){
        printf(" Queue is already empty. ");
        return;
    }

    if(q->front==q->rear) { // last element
        q->front = -1;
        q->rear = -1;
        return;
    }
    q->data[q->front] = 0;
    q->front = (q->front + 1) % q->capacity;
    return;
}

void getAll(cqueue *q){
    if(empty(q)){ printf("Q is empty\n"); return; }
    int i = q->front;
    while(1){
        printf("%d ", q->data[i]);
        if(i == q->rear) break;
        i = (i + 1) % q->capacity;
    }
    printf("\n");
}

int main(){
    int cap = 15;
    cqueue *q = qinit(cap,-1,-1);
    for(int i=0;i<30;i++){
        enq(q, i);
        getAll(q);
    }
    
    for(int i=0;i<30;i++){
        deque(q);
        getAll(q);
    }
    freeq(q);
    return 0;
}