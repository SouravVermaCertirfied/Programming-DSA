#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_CONSUMERS 5
#define MAX_PRODUCERS 50
#define BUFFER_CAPACITY 10   // Bounded buffer size

// Node for each job
typedef struct tNode_t {
    int val;
    struct tNode_t *next;
} tNode_t;

// Queue structure with capacity
typedef struct jobQueue_t {
    tNode_t *head;
    tNode_t *tail;
    int done;        // number of finished producers
    int size;        // current queue size
    int capacity;    // max allowed size
} jobQueue_t;

int total = 0;
pthread_mutex_t totalLock;

pthread_mutex_t qLock;
pthread_cond_t qCond;

// Enqueue with blocking if buffer full
void enQ(jobQueue_t *jQ, tNode_t *newNode) {
    pthread_mutex_lock(&qLock);

    // Block producers if buffer is full
    while (jQ->size >= jQ->capacity) {
        pthread_cond_wait(&qCond, &qLock);  // wait until space available
    }

    if (jQ->tail) {
        jQ->tail->next = newNode;
    } else {
        jQ->head = newNode;
    }
    jQ->tail = newNode;

    jQ->size++;  // increase current size

    pthread_cond_broadcast(&qCond);  // wake consumers
    pthread_mutex_unlock(&qLock);
}

// Dequeue with signaling for producers
int deQ(jobQueue_t *jQ) {
    if (jQ->head == NULL) {
        return -1;  // empty
    }

    tNode_t *temp = jQ->head;
    int val = temp->val;

    if (jQ->head == jQ->tail) {
        jQ->head = NULL;
        jQ->tail = NULL;
    } else {
        jQ->head = jQ->head->next;
    }

    free(temp);

    jQ->size--;  // decrease current size
    pthread_cond_broadcast(&qCond);  // wake any producers waiting for space

    return val;
}

// Consumer thread
void *consumer(void *args) {
    jobQueue_t *jQ = (jobQueue_t *)args;

    while (1) {
        pthread_mutex_lock(&qLock);

        while (jQ->size == 0 && jQ->done < MAX_PRODUCERS) {
            pthread_cond_wait(&qCond, &qLock);
        }

        if (jQ->size == 0 && jQ->done >= MAX_PRODUCERS) {
            pthread_mutex_unlock(&qLock);
            break;
        }

        int tempval = deQ(jQ);  // dequeue and reduce size
        pthread_mutex_unlock(&qLock);

        if (tempval != -1) {
            pthread_mutex_lock(&totalLock);
            total += tempval;
            pthread_mutex_unlock(&totalLock);
        }
    }

    return NULL;
}

// Producer thread
void *producer(void *args) {
    jobQueue_t *jQ = (jobQueue_t *)args;

    for (int i = 0; i < 100; i++) {
        tNode_t *newNode = (tNode_t *)malloc(sizeof(tNode_t));
        newNode->val = i;
        newNode->next = NULL;
        enQ(jQ, newNode);  // will block if buffer is full
    }

    pthread_mutex_lock(&qLock);
    jQ->done += 1;              // mark this producer done
    pthread_cond_broadcast(&qCond); // wake consumers
    pthread_mutex_unlock(&qLock);

    return NULL;
}

int main() {
    pthread_t conThreadPool[MAX_CONSUMERS];
    pthread_t proThreadPool[MAX_PRODUCERS];

    pthread_mutex_init(&qLock, NULL);
    pthread_cond_init(&qCond, NULL);

    jobQueue_t jQ = {
        .head = NULL,
        .tail = NULL,
        .done = 0,
        .size = 0,              // initialize size
        .capacity = BUFFER_CAPACITY  // set capacity
    };

    pthread_mutex_init(&totalLock, NULL);

    // Start consumers first
    for (int i = 0; i < MAX_CONSUMERS; i++)
        pthread_create(&conThreadPool[i], NULL, consumer, &jQ);

    // Start producers
    for (int i = 0; i < MAX_PRODUCERS; i++)
        pthread_create(&proThreadPool[i], NULL, producer, &jQ);

    // Join producers first
    for (int i = 0; i < MAX_PRODUCERS; i++)
        pthread_join(proThreadPool[i], NULL);

    // After producers are done, wake all consumers
    pthread_mutex_lock(&qLock);
    pthread_cond_broadcast(&qCond);
    pthread_mutex_unlock(&qLock);

    // Join consumers
    for (int i = 0; i < MAX_CONSUMERS; i++)
        pthread_join(conThreadPool[i], NULL);

    pthread_mutex_destroy(&qLock);
    pthread_cond_destroy(&qCond);
    pthread_mutex_lock(&totalLock);
    int temp = total;
    pthread_mutex_unlock(&totalLock);
    pthread_mutex_destroy(&totalLock);

    printf("The total sum value is: %d\n", temp);

    return 0;
}