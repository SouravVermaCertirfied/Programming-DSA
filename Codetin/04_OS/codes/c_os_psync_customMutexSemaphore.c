#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Custom implementation of __sync_lock_test_and_set
// This function atomically sets the value of *ptr to "value" and returns the old value of *ptr.
// It uses an assembly-level atomic exchange operation to ensure mutual exclusion.
int custom_sync_lock_test_and_set(int *ptr, int value) {
    int old_value;

    // Assembly code to atomically exchange the value of *ptr with "value".
    // "lock" ensures atomicity in a multi-processor environment (the lock prefix guarantees the operation is atomic).
    // "xchg" exchanges the values of two operands: the value at *ptr and the provided "value".
    // The result is that the old value of *ptr is stored in "old_value", and *ptr is updated with the new "value".
    __asm__ volatile (
        "lock; xchg %0, %1"  // Atomically exchange *ptr with value
        : "=r"(old_value), "=m"(*ptr)  // Output operands: old_value gets the original value of *ptr
        : "r"(value)  // Input operand: "value" is the new value to store in *ptr
        : "memory"  // Tells the compiler that memory will be modified by the assembly block
    );

    // Return the old value of *ptr before it was set to the new "value"
    return old_value;
}

// Custom mutex structure
typedef struct {
    volatile int locked; // 0 means unlocked, 1 means locked
} custom_mutex_t;

// Initialize the custom mutex
// This function sets the initial state of the mutex to unlocked (0).
void custom_mutex_init(custom_mutex_t *mutex) {
    mutex->locked = 0;  // Mutex is initially unlocked
}

// Lock the custom mutex
// This function will repeatedly attempt to acquire the lock (i.e., set "locked" to 1).
// It uses a spinlock mechanism, busy-waiting until the lock is available.
void custom_mutex_lock(custom_mutex_t *mutex) {
    while (custom_sync_lock_test_and_set(&mutex->locked, 1)) {
        // Spin-wait (busy-wait) until the mutex is unlocked (i.e., the locked flag is 0).
        // The custom_sync_lock_test_and_set function will atomically set the "locked" flag to 1 and return the old value.
        // If the mutex is already locked, it will return 1, causing the thread to keep busy-waiting until the lock is released.
        usleep(1);  // Optional: small sleep to prevent 100% CPU usage while spinning.
    }
}

// Unlock the custom mutex
// This function sets the "locked" flag to 0, which releases the lock.
void custom_mutex_unlock(custom_mutex_t *mutex) {
    mutex->locked = 0;  // Unlock the mutex by setting the "locked" flag to 0.
}

// Critical section function
// This function simulates a critical section where a thread performs work that needs exclusive access.
void* critical_section(void* arg) {
    custom_mutex_t* mutex = (custom_mutex_t*)arg;  // Extract the custom mutex passed as an argument.

    // Lock the custom mutex to enter the critical section
    custom_mutex_lock(mutex);

    // Entering critical section
    printf("Thread %ld entering critical section\n", (long)pthread_self());

    // Simulate work inside the critical section
    // This loop represents the work being done while the thread holds the mutex.
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
    custom_mutex_init(&mutex);  // Initialize the mutex to the unlocked state (locked = 0).

    // Create two threads that will access the critical section
    pthread_t thread1, thread2;
    
    // Create the first thread
    pthread_create(&thread1, NULL, critical_section, (void*)&mutex);
    
    // Create the second thread
    pthread_create(&thread2, NULL, critical_section, (void*)&mutex);

    // Wait for both threads to finish
    // This ensures the main thread waits for the completion of both threads before exiting.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
