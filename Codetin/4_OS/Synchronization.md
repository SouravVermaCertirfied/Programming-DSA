# Synchronization

## Consumer-Producer Problem
Key requirments of the problem:  
1. Consumer should only consume if the buffer is not empty.
2. Producer should only produce if the buffer is not full.
3. If the buffer is empty, the consumer needs to wait.
4. If the buffer is empty, the producer needs to wait.
5. Avoid the Race Condition.

Let's solve this question in two approch:  
1. Simpler Approch : Use only one `mutex`. Here, the limitaion will be that consumer and producer will keep running even when they are not consuming and producing, hence using up more CPU cycles.
2. Better Approch : Use **condition variables** `full` and `empty`. to ensure that CPU cycles are not wasted.

## Simple Approach - use only `mutex`
```c
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE]
int in = 0;
int out = 0;

pthread_mutex_t mutex; // for sync threads

/* Producer  function */

void *producer(void *args){
    while(1){
        int item = (int)rand(); // Produce 0-99 range random number
        pthread_mutex_lock(&mutex); // lock mutex before entering critical section
        if( (( in +1 )% BUFFER_SIZE ) != out ){ // checks buffer is not full
            buffer[in] = item; 
            printf("Produced : %d", item);
            in = (in + 1) % BUFFER_SIZE;
        }
        pthread_mutex_unlock(&mutex); // unlock mutex
    }

void *consumer(void *args){
    while(1){
        pthread_mutex_lock(&mutex); // lock mutex before entering critical section
        if( in != out ){ // ensure that buffer is not empty
        int item = buffer[out];
        printf("Consumed : %d", item);
        out = (out + 1 ) % BUFFER_SIZE;
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(){

    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);

    pthread_create_(&prod, NULL, producer, NULL);
    pthread_create_(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
```

## Better Approach - Using `mutex` and conditions `full` and `empty`

```c
#include<pthread.h>

#define BUFFER_SIZE 5

pthread_mutex_t mutex;

pthread_cond_t full;
pthread_cond_t empty;

void *producer(void *args){
    int item = (int)rand();
    pthread_mutex_lock(&mutex);



    pthread_mutex_unlock(&mutex);
}

void *consumer(void *args){
    pthread_mutex_lock(&mutex);


    pthread_mutex_unlock(&mutex);
}

```
    
    