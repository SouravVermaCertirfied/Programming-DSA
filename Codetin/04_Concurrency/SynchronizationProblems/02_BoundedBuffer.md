# Bounded Buffer
> Solved using mutex and condition variable.

Following are the items to be taken care when writing bounded buffer:

1. Correct synchronization
2. Robustness : Error checking, Check if memory not allocated, thread not created
3. Multiple producer-consumer support
4. Graceful shutdown strategy: do not let it run infinite, make a condition where it exits
5. Always ask tradeof:
    1. ease of coding making things global
    2. branching over sacrifising a slot

Here is a code that full fills these items

```c
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 16

/* Effective capacity = BUFFER_SIZE - 1 */
int buffer[BUFFER_SIZE];

int front = 0;
int rear  = 0;

bool shutdown_requested = false;

pthread_mutex_t lock;
pthread_cond_t can_read;
pthread_cond_t can_write;

static bool is_full(void){
    return ((rear + 1) % BUFFER_SIZE) == front;
}

static bool is_empty(void){
    return rear == front;
}

static void enqueue(int value){
    buffer[rear] = value;
    rear = (rear + 1) % BUFFER_SIZE;
}

static int dequeue(void){
    int value = buffer[front];
    front = (front + 1) % BUFFER_SIZE;
    return value;
}

static int init_all(void){
    if (pthread_mutex_init(&lock, NULL) != 0)
        return -1;
    if (pthread_cond_init(&can_read, NULL) != 0)
        return -1;
    if (pthread_cond_init(&can_write, NULL) != 0)
        return -1;
    return 0;
}

static void destroy_all(void){
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&can_read);
    pthread_cond_destroy(&can_write);
}

static void request_shutdown(void)
{
    pthread_mutex_lock(&lock);
    shutdown_requested = true;
    pthread_cond_broadcast(&can_read);
    pthread_cond_broadcast(&can_write);
    pthread_mutex_unlock(&lock);
}

void *producer_thread(void *arg){
    int value = *(int *)arg;
    while (true)    {
        pthread_mutex_lock(&lock);
        while (is_full() && !shutdown_requested)        {
            pthread_cond_wait(&can_write, &lock);
        }
        if (shutdown_requested)        {
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        enqueue(value++);
        pthread_cond_signal(&can_read);
        pthread_mutex_unlock(&lock);
    }
}

void *consumer_thread(void *arg){
    (void)arg;
    while (true)    {
        pthread_mutex_lock(&lock);
        while (is_empty() && !shutdown_requested){
            pthread_cond_wait(&can_read, &lock);
        }
        if (is_empty() && shutdown_requested)        {
            pthread_mutex_unlock(&lock);
            return NULL;
        }

        int value = dequeue();
        pthread_cond_signal(&can_write);
        pthread_mutex_unlock(&lock);
        printf("Consumed %d\n", value);
    }
}

int main(void){
    if (init_all() != 0)    {
        fprintf(stderr, "Initialization failed\n");
        return EXIT_FAILURE;
    }

    pthread_t producers[2];
    pthread_t consumers[2];

    int seed1 = 0;
    int seed2 = 1000;

    pthread_create(&producers[0], NULL, producer_thread, &seed1);
    pthread_create(&producers[1], NULL, producer_thread, &seed2);

    pthread_create(&consumers[0], NULL, consumer_thread, NULL);
    pthread_create(&consumers[1], NULL, consumer_thread, NULL);

    sleep(3);

    request_shutdown();

    pthread_join(producers[0], NULL);
    pthread_join(producers[1], NULL);

    pthread_join(consumers[0], NULL);
    pthread_join(consumers[1], NULL);

    destroy_all();

    return 0;
}
```
