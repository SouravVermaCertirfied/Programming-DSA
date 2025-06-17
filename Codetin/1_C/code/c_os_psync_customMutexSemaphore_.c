#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Define the custom mutex structure
typedef struct {
    volatile int locked; // 0 means unlocked, 1 means locked
} custom_mutex_t;

// Initialize the custom mutex
void custom_mutex_init(custom_mutex_t *mutex) {
    mutex->locked = 0;  // Mutex is initially unlocked
}

// Lock the custom mutex
void custom_mutex_lock(custom_mutex_t *mutex) {
    while (__sync_lock_test_and_set(&mutex->locked, 1)) {
        // Spin-wait (busy-wait) until the mutex is unlocked
        // __sync_lock_test_and_set is an atomic operation
        usleep(1);  // Optional: small sleep to prevent 100% CPU usage
    }
}

// Unlock the custom mutex
void custom_mutex_unlock(custom_mutex_t *mutex) {
    mutex->locked = 0;  // Unlock the mutex
}

// Critical section function
void* critical_section(void* arg) {
    custom_mutex_t* mutex = (custom_mutex_t*)arg;

    // Lock the custom mutex to enter the critical section
    custom_mutex_lock(mutex);

    // Entering critical section
    printf("Thread %ld entering critical section\n", (long)pthread_self());

    // Simulate work inside the critical section
    for (int i = 0; i < 5; i++) {
        printf("Thread %ld working in critical section, step %d\n", (long)pthread_self(), i + 1);
    }

    // Leaving critical section
    printf("Thread %ld leaving critical section\n", (long)pthread_self());

    // Unlock the custom mutex to allow other threads to enter
    custom_mutex_unlock(mutex);

    return NULL;
}

int main() {
    // Create and initialize the custom mutex
    custom_mutex_t mutex;
    custom_mutex_init(&mutex);

    // Create two threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, critical_section, (void*)&mutex);
    pthread_create(&thread2, NULL, critical_section, (void*)&mutex);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
    