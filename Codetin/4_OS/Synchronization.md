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
        int item = rand() % 100; // Produce 0-99 range random number
        pthread_mutex_lock(&mutex); // lock mutex before entering critical section
        if( (( in +1 )% BUFFER_SIZE ) != out ){
            buffer[in] = item;
            printf("Produced : %d", item);
            in = (in + 1) % BUFFER_SIZE;
        }
        pthread_mutex_unlock(&mutex);


    }
}
```
    
    