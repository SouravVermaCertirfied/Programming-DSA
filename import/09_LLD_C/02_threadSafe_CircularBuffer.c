/*
* Thread-safe circular buffer for integers.
* Supports a producer writing into the buffer and a consumer reading & clearing it.
* Synchronization is handled using pthread mutex and condition variables to avoid
* race conditions and deadlocks. Producer waits if buffer is full, consumer waits
* if buffer is empty.
*/

/*
====================================================
        PRODUCER–CONSUMER (pthread) – QUICK NOTES
====================================================

• Shared buffer (e.g., circular queue) is accessed by
  producer and consumer threads.

• pthread_mutex_t
  - Provides mutual exclusion.
  - Must be locked before accessing shared data.
  - Only one thread can enter critical section at a time.

• pthread_cond_t
  - Used for thread synchronization.
  - Threads wait until a condition becomes true.
  - Always used together with a mutex.

• pthread_cond_wait(cond, mutex)
  - Must be inside a WHILE loop (not IF).
  - Atomically releases mutex and puts thread to sleep.
  - Reacquires mutex when awakened.

    while (condition_not_met) {
        pthread_cond_wait(&cond, &lock);
    }

• Producer logic:
  - Wait while buffer is FULL.
  - Insert item into buffer.
  - Signal consumer after producing.

• Consumer logic:
  - Wait while buffer is EMPTY.
  - Remove item from buffer.
  - Signal producer after consuming.

• Correct sequence (IMPORTANT) - this should be inside while loop:
  🧠 lock → check condition → modify data → signal → unlock

• Common mistakes:
  - Using IF instead of WHILE with cond_wait
  - Waiting without holding mutex
  - Signaling before changing shared state
  - Locking mutex once for entire loop
  - Not passing shared data to threads

• One-line summary:
  Mutex protects shared data,
  Condition variables coordinate thread execution.

====================================================
*/


#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#define CAP 10u

pthread_mutex_t lock;
pthread_cond_t cond;

typedef struct CircularQueue{
    int *data;
    int front;
    int rear;
    int cap;
} CircularQueue;

CircularQueue *CircularQueue_Init(int cap){
    CircularQueue *cq = (CircularQueue *)malloc(sizeof(CircularQueue));
    cq->data = (int *)malloc(sizeof(int)*cap);
    cq->front  = -1;
    cq->rear = -1;
    cq->cap = cap;
    return cq;
}

void CircularQueue_Free(CircularQueue *cq){
    free(cq->data);
    free(cq);
    return;
}

bool isEmpty(CircularQueue *cq){
    if(cq->front == -1)
        return true;
    return false;
}

bool isFull(CircularQueue *cq){
    if(((cq->rear + 1 )% cq->cap) == (cq->front))
        return true;
    return false;
}

void *consumer(void *args) {
    CircularQueue *cq = args;

    while (1) {
        pthread_mutex_lock(&lock);
        while (isEmpty(cq)) {
            pthread_cond_wait(&cond, &lock);
        }
        int val = cq->data[cq->front];
        printf("Consuming %d\n", val);
        if (cq->front == cq->rear) {
            cq->front = cq->rear = -1;
        } else {
            cq->front = (cq->front + 1) % cq->cap;
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        if (val == 99) break;
    }
    return NULL;
}


void *producer(void *args) {
    CircularQueue *cq = args;
    int item = 0;

    while (item < 100) {
        pthread_mutex_lock(&lock);
        while (isFull(cq)) {
            pthread_cond_wait(&cond, &lock);
        }
        if (isEmpty(cq)) {
            cq->front = cq->rear = 0;
        } else {
            cq->rear = (cq->rear + 1) % cq->cap;
        }
        cq->data[cq->rear] = item;
        printf("Produced %d\n", item);
        item++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}


int main(){
    printf("\n**Starting the program.**");
    CircularQueue *cq = CircularQueue_Init(CAP);
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t pro, con;
    pthread_create(&pro, NULL, producer, cq);
    pthread_create(&con, NULL, consumer, cq);

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    
    printf("\n**Ending the program.**");

    return 0;
}