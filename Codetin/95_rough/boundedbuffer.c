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

#define CAP 10

typedef struct cqueue_t{
    int front;
    int rear;
    int size;
    int cap;

    int buff[CAP];

    pthread_mutex_t qlock;
    pthread_cond_t qcond;
} cqueue_t;

cqueue_t cq;

void cqInit(){
    cq.front = -1;
    cq.rear = -1;
    cq.size = 0;
    cq.cap = CAP;
    pthread_mutex_init(&cq.qlock, NULL);
    pthread_cond_init(&cq.cond, NULL);
}

void cqDestroy(){
    cq.front = -1;
    cq.rear = -1;
    cq.size = 0;
    cq.cap = CAP;
    pthread_destroy(&cq.qlock);
    pthread_destroy(&cq.cond);
}

void cenque(int item){
    if(cq.front==-1){
        cq.front = 0;
    }
    cq.rear = (cq.rear+1)%cq.cap;
    cq.buff[rear]=item;
    size++;
}

void cdequeue(int)

void* producer(void *args){
    for(int i=0; i<100; i++){
        pthread_mutex_lock(&cq.lock);
        while(!isEmpty()){
            pthread_cond_wait(&cq.cond, &cq.lock);
        }
        int item = 5;
        cenque(item);
        pthread_cond_signal(&cq.cond);
        pthread_mutex_unlock(&cq.lock);
    }
    return NULL;
}

void* consumer(void *args){
    while(1){
        pthread_mutex_lock(&cq.lock);
        while(isEmpty()){
            pthread_cond_wait(&cq.cond, &cq.lock);
        }
        int item;
        item = cdequeue();
        pthread_mutex_unlock(&cq.lock);
        item = 
    }
}

int main(){
    cqInit();



    cqDestroy();
    return 0;
}

