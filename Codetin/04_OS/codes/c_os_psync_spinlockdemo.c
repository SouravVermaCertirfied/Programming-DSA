#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Spinlock variable. 
// '0' means unlocked, '1' means locked. 
// This will be shared among threads.
volatile int spinlock = 0;  

// Function to acquire the lock using a spinlock mechanism
void acquire_lock(volatile int *lock) {
    // The __sync_lock_test_and_set() function atomically sets the lock to '1' 
    // and returns the previous value of the lock.
    // If the lock was already '1' (locked), it will return '1' and the thread will continue spinning
    // (repeatedly checking) until the lock is available (i.e., it becomes '0').
    while (__sync_lock_test_and_set(lock, 1)) {
        // Spin (i.e., keep checking the lock) until it becomes available.
        // The thread will be "busy-waiting" here.
        // This is called a spinlock, which is efficient only for short-term locks.
    }
}

// Function to release the lock
void release_lock(volatile int *lock) {
    // Set the lock back to '0' (unlocked).
    // This will allow other threads that are waiting to acquire the lock to proceed.
    *lock = 0;
}

// Function to simulate the critical section accessed by threads
void *critical_section(void *arg) {
    // Try to acquire the lock
    acquire_lock(&spinlock);

    // Once the lock is acquired, the thread enters the critical section
    printf("Thread %ld is in critical section.\n", (long)pthread_self());
    
    // Simulate some work inside the critical section (e.g., processing or data manipulation).
    // We use sleep(1) here to simulate that work takes some time.
    sleep(1);  

    // After the work is done, the thread will release the lock, allowing others to access the critical section.
    release_lock(&spinlock);

    return NULL;
}

int main() {
    pthread_t threads[5];  // Array to hold thread identifiers.

    // Create 5 threads. Each thread will run the critical_section function.
    for (int i = 0; i < 5; i++) {
        // Create a new thread, which will execute the critical_section function.
        // We are passing NULL as the argument to critical_section, as it doesn't require any arguments.
        pthread_create(&threads[i], NULL, critical_section, NULL);
    }

    // Wait for all threads to finish execution.
    // We call pthread_join for each thread to ensure that the main thread waits until all the threads complete.
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Once all threads have completed their execution, the main function ends.
    return 0;
}
