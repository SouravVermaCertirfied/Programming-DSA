
# Advanced Concurrency in C

## Thread Pools (Managing Many Threads Efficiently)

A **thread pool** is a collection of threads that are created once and used to perform multiple tasks. Instead of creating and destroying threads for each task, which is expensive, a pool of worker threads is kept alive and reused.

### Why Use Thread Pools?
- Reduces overhead of thread creation/destruction
- Efficient resource utilization
- Helps control concurrency level

### Example: Simple Thread Pool in C

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define TASK_QUEUE_SIZE 10

typedef struct {
    void (*function)(void*);
    void *arg;
} task_t;

task_t task_queue[TASK_QUEUE_SIZE];
int task_count = 0;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t task_ready = PTHREAD_COND_INITIALIZER;

void* worker(void* arg) {
    while (1) {
        pthread_mutex_lock(&queue_lock);
        while (task_count == 0)
            pthread_cond_wait(&task_ready, &queue_lock);

        task_t task = task_queue[--task_count];
        pthread_mutex_unlock(&queue_lock);

        task.function(task.arg);
    }
    return NULL;
}

void thread_pool_add_task(void (*function)(void*), void* arg) {
    pthread_mutex_lock(&queue_lock);
    task_queue[task_count++] = (task_t){function, arg};
    pthread_cond_signal(&task_ready);
    pthread_mutex_unlock(&queue_lock);
}

void print_number(void* arg) {
    int num = *(int*)arg;
    printf("Processing %d\n", num);
    sleep(1);
}

int main() {
    pthread_t pool[THREAD_POOL_SIZE];
    for (int i = 0; i < THREAD_POOL_SIZE; ++i)
        pthread_create(&pool[i], NULL, worker, NULL);

    for (int i = 0; i < 20; ++i) {
        int* num = malloc(sizeof(int));
        *num = i;
        thread_pool_add_task(print_number, num);
    }

    sleep(5);
    return 0;
}
```

---

## Producer-Consumer Pattern

This pattern involves two types of threads: **producers** generate data and place it in a buffer; **consumers** take data from the buffer.

### Implementation (Using Mutex and Condition Variables)

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);
        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &lock);

        buffer[count++] = i;
        printf("Produced %d\n", i);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);
        while (count == 0)
            pthread_cond_wait(&not_empty, &lock);

        int item = buffer[--count];
        printf("Consumed %d\n", item);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
```

---

## Deadlocks and Livelocks

### Deadlock Example

```c
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1_func(void* arg) {
    pthread_mutex_lock(&lock1);
    sleep(1);
    pthread_mutex_lock(&lock2);
    printf("Thread 1 acquired both locks\n");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* thread2_func(void* arg) {
    pthread_mutex_lock(&lock2);
    sleep(1);
    pthread_mutex_lock(&lock1);
    printf("Thread 2 acquired both locks\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}
```

🔁 Both threads hold one lock and wait for the other — this leads to deadlock.

### Livelock

Occurs when threads keep changing state to avoid deadlock but make no progress.

```c
// Not shown: logic with retries and backoff; both threads give way repeatedly
```

---

## Thread-Local Storage (TLS)

Allows each thread to maintain its own separate copy of a variable.

### Using `__thread` keyword (GCC)

```c
#include <stdio.h>
#include <pthread.h>

__thread int tls_var;

void* thread_func(void* arg) {
    tls_var = *(int*)arg;
    printf("Thread %ld: tls_var = %d\n", pthread_self(), tls_var);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int a = 1, b = 2;

    pthread_create(&t1, NULL, thread_func, &a);
    pthread_create(&t2, NULL, thread_func, &b);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
```

Each thread gets its own version of `tls_var` — changes are not visible to other threads.

---

## Summary

| Feature             | Use Case                                |
|---------------------|------------------------------------------|
| Thread Pool         | Efficient task processing                |
| Producer-Consumer   | Coordinating producers & consumers       |
| Deadlock            | When threads wait on each other          |
| Livelock            | No progress despite state changes        |
| Thread-Local Storage| Per-thread variable isolation            |
