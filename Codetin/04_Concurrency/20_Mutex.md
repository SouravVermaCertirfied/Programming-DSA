## ☢️Important syntax ( C / pthread )
For condition variables.
```cpp
pthread_cond_t  cond;         // declaration

pthread_cond_wait(&cond, &mutex);      // Release mutex, wait for signal, then re-lock - usually used within a while loop
pthread_cond_signal(&cond);             // Wake up one waiting thread
pthread_cond_broadcast(&cond);          // Wake up all waiting threads
```

## Consumer Producer Problem ( Bounded Buffer )
- Requirements to be full filled by the program:
    - Multiple producers
    - Multiple consumers
    - Fixed buffer size
    - No busy waiting
- Why This Is Correct (Say This) ?
    - mutex protects buffer, count, in, out
    - while prevents spurious wakeups
    - State is updated before signaling
    - No busy waiting
    - Circular buffer avoids shifting data
    - Multiple producers & consumers supported

```cpp
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 5

int buffer[BUFFER_SIZE];
int count = 0;          // number of items in buffer
int in = 0;             // write index
int out = 0;            // read index

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

/* Producer thread */
void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        int item = id * 100 + i;

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Producer %d produced %d (count=%d)\n", id, item, count);

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);

        usleep(100000); // simulate work
    }
    return NULL;
}

/* Consumer thread */
void* consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumer %d consumed %d (count=%d)\n", id, item, count);

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        usleep(150000); // simulate work
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int prod_ids[NUM_PRODUCERS];
    int cons_ids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        prod_ids[i] = i;
        pthread_create(&producers[i], NULL, producer, &prod_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        cons_ids[i] = i;
        pthread_create(&consumers[i], NULL, consumer, &cons_ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    printf("All producers and consumers finished.\n");
    return 0;
}

```

---
<div style="display: flex; justify-content: space-between;">
    <a href="12_PriorityInversion.md">← 12_PriorityInversion.md</a>
    <a href="21_ConditionVariables.md">21_ConditionVariables.md →</a>
</div>