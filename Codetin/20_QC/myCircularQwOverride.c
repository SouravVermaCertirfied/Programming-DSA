/*
3. Medium – Circular Buffer with Overwrite
Question:
    Design a circular buffer without over support.
    When the buffer is full and a new element cannot be enqued.
Operations:
    enqueue(x) – overwrite if full, overwrites the oldest element in case of overflow
    dequeue() – remove the oldest element
    getAll() – return current contents in order
    
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int cap;
    int front;
    int rear;
    int *data;
} cque;

cque *newCque(int cap, int f, int r){
    cque *temp = (cque*)malloc(sizeof(cque));;
    if(temp){
        int *d = (int*)calloc(cap, sizeof(int));
        if(d){
            temp->data = d;
            temp->front = -1;
            temp->rear = -1;
            temp->cap = cap;
            return temp;
        }
        free(temp);
    }
    return NULL;
}

void qfree(cque *q){
    free(q->data);
    free(q);
    return ;
}

char empty(cque *q){
    if(q->front == -1)
        return 1;
    return 0;
}

void enqueue(cque *q, int x){
    if(q->front == -1)
        q->front = 0;
    else if(((q->rear + 1 ) % q->cap) == q->front) { // queue is full
        q->front = (q->front + 1) % q->cap;
    }
    q->rear = (q->rear+1) % q->cap;
    q->data[q->rear] = x;
    return;
}

void dequeue(cque *q){
    if(empty(q)){
        printf("q is already empty\n");
        return;
    }
    q->data[q->front] = -1;
    if(q->front==q->rear){
        q->front = -1;
        q->rear = -1;
        return;
    }
    q->front = (q->front+1) % q->cap;
    return;
}


void getall(cque *q){
    if(empty(q)){ 
        printf("Q is empty\n"); 
        return; 
    }
    int i = q->front;
    while(1){
        printf("%d ", q->data[i]);
        if(i == q->rear) break;
        i = (i + 1) % q->cap;
    }
    printf("\n");
}

int main(){
    int cap = 10;
    cque *q = newCque(cap, -1, -1);
    printf("Now enque\n");
    for(int i=0; i<15; i++){
        enqueue(q, i);
        getall(q);
    }
    printf("Now dequeu\n");
    for(int i=0; i<15; i++){
        dequeue(q);
        getall(q);
    }
    qfree(q);
    printf("program ends");
    return 0;
}