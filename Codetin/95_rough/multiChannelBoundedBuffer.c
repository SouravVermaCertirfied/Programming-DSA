/*
**Problem Statement:**
Implement a multi-channel bounded buffer system that allows independent channels to operate in parallel.

**Requirements:**

* Use pure **C** and **POSIX threads (`pthreads`)**.
* Maintain `N` independent, fixed-size integer buffers (channels).
* Implement `void init_system()`.
* Implement `void produce(int channel_id, int item)`:
* Blocks if the specific channel is full.


* Implement `int consume(int channel_id)`:
* Blocks if the specific channel is empty.

* let there be 4 consumers , 5 producers and 3 channels
* any consumer/producer access any channel


* **Concurrency Constraint:** A thread accessing Channel 0 must **never** block or lock out a thread accessing Channel 1.
* Minimize global locking to maximize throughput.
*/

#include<pthread.h>
#include<stdio.h>

#define CHANNEL_N      (3u)
#define CHANNEL_SIZE   (10u)
#define PRODUCER_N       (5u)
#define CONSUMER_N       (3u)


typedef struct channel_t{
    int size;
    int front;
    int rear;
    int cap;

    int buff[CHAN_SIZE];

    pthread_mutex_t clock;
    pthread_cond_t ccond;
} channel_t;

channel_t chan[CHANNEL_SIZE];

void init_system(){
    // init the channels
    for(int i=0; i<CHANNEL_N;i++){
        chan[i].size = 0;
        chan[i].front = 0;
        chan[i].rear = 0;
        chan[i].cap = CHANNEL_SIZE;

        pthread_mutex_init(&chan[i].clock, NULL);
        pthread_condattr_init(&chan[i].ccond, NULL);
    }
}

int main(){
    pthread_t pros[]

    return 0;
}
