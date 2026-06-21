#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10
#define NUM_ITEMS 20

int buffer[MAX_BUFFER_SIZE];
int count = 0;       // number of items in the buffer
int in = 0;          // index for next produced item
int out = 0;         // index for next consumed item
int finished = 0;    // flag to signal end of production

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 1; i <= NUM_ITEMS; ++i) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is full
        while (count == MAX_BUFFER_SIZE)
            pthread_cond_wait(&cond_full, &mutex);

        // Produce item
        buffer[in] = i;
        in = (in + 1) % MAX_BUFFER_SIZE;
        count++;

        printf("Producer %d produced item %d (buffer size: %d)\n", id, i, count);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_empty);

        usleep(100000);  // sleep for 100ms
    }

    // Signal finished
    pthread_mutex_lock(&mutex);
    finished = 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond_empty);

    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is empty
        while (count == 0 && !finished)
            pthread_cond_wait(&cond_empty, &mutex);

        // Exit when done
        if (count == 0 && finished) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        // Consume item
        int item = buffer[out];
        out = (out + 1) % MAX_BUFFER_SIZE;
        count--;

        printf("Consumer %d consumed item %d (buffer size: %d)\n", id, item, count);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_full);

        usleep(150000);  // sleep for 150ms
    }

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;
    int prod_id = 1, cons_id = 1;

    pthread_create(&prod_thread, NULL, producer, &prod_id);
    pthread_create(&cons_thread, NULL, consumer, &cons_id);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    printf("All work done!\n");
    return 0;
}
