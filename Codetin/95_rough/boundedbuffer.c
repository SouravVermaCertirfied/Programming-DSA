/*
RequirementsFixed Capacity: 

The buffer must have a maximum capacity $N$ allocated at initialization.Blocking

 Operations: * 

1. If the buffer is full, any producer thread attempting to write must block (wait) until space becomes available.
2. If the buffer is empty, any consumer thread attempting to read must block (wait) until data becomes available.
3. Thread Safety: You must use appropriate synchronization primitives (e.g., mutexes, condition variables, or semaphores) to ensure no data races occur.
4. Efficiency: Avoid busy-waiting (polling loops like while(full);). 
5. Threads must sleep efficiently when blocked.

*/
#include<stdio.h>
#include<pthread.h>

#define N 10

typedef struct cqueue_t{
    int buff[N];
    int cap;
    int front;
    int rear;


    pthread_mutex_t qlock;
    pthread_cond_t qcond;
} cqueue_t;

cqueue_t cq;

bool isEmpty(){
    if(cq.front==-1)
        return true;
    if((cq.rear+1%cq.cap) != cq.front)
        return true;
    return false;
}

void enqueue(int item){
    if(isEmpty()){
        // first item
        if(cq.front==-1){
            cq.front++;
        }
        //any other item
        cq.rear = (cq.rear+1)%cq.cap;
        cq.buff[cq.rear] = item;
    }
}

int dequeue(){
    int ret;
    if(!isEmpty()){
        if(cq.front==cq.rear){
            ret = cq.buff[cq.front];
            cq.front=-1;
            cq.rear = -1;
        }
        else{
            ret = cq.buff[cq.front];
            cq.front = (cq.front+1)%cq.cap;
        }
    }
    return ret;
}

void* producer(void *args){
    for(int i=0; i<100; i++){
        pthread_mutex_lock(&cq.qlock);
        while(!isEmpty()){
            pthread_cond_wait(&cq.qcond, &cq.qlock);
        }
        int rand = 5;
        enqueue(i);
        printf("inserted i = %d \n", i);
        pthread_cond_signal(&cq.qcond);
        pthread_mutex_unlock(&cq.qlock);
    }
    return NULL;
}

void* consumer(void *args){
    while(1){
        pthread_mutex_lock(&cq.qlock);
        while(isEmpty()){
            pthread_cond_wait(&cq.qcond, &cq.qlock);
        }
        int ret = dequeue();
        printf("extracted val = %d \n", ret);
        pthread_mutex_unlock(&cq.qlock);
    }
    return NULL;
}

void cqinit(){
    cq.front = -1;
    cq.rear = -1;
    cq.cap = N;

    pthread_mutex_init(&cq.qlock, NULL);
    pthread_cond_init(&cq.qcond, NULL);
}

void cdestroy(){
    cq.front = -1;
    cq.rear = -1;

    pthread_mutex_destroy(&cq.qlock);
    pthread_cond_destroy(&cq.qcond);
}

int main(){
    pthread_t pro[5], con[5];
    for(int i=0; i<5; i++){
        pthread_create(&pro[i], NULL, producer, NULL);
        pthread_create(&con[i], NULL, consumer, NULL);
    }
    for(int i=0; i<5; i++){
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }
    
    return 0;
}