#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

// Shared variables
volatile bool flag[2] = {false, false};  // Flags for P0 and P1
volatile int turn = 0;  // Turn variable to control whose turn it is

// Critical section simulation
void critical_section(int process_id) {
    printf("Process P%d is in the critical section.\n", process_id);
}

// Peterson's Algorithm for mutual exclusion
void peterson(int process_id) {
    int other = 1 - process_id;  // If process_id is 0, other is 1; if process_id is 1, other is 0
    
    // Entry Section
    flag[process_id] = true;  // Indicate the process wants to enter the critical section
    turn = other;  // Give the other process a chance to enter
    
    // Wait until it's not the other process's turn or the other process is not interested
    while (flag[other] && turn == other) {
        // Busy-wait (spinlock)
    }
    
    // Critical Section
    critical_section(process_id);
    
    // Exit Section
    flag[process_id] = false;  // Indicate the process is done with the critical section
}

// Process P0
void* process_0(void* arg) {
    while (1) {
        peterson(0);  // Process P0
    }
    return NULL;
}

// Process P1
void* process_1(void* arg) {
    while (1) {
        peterson(1);  // Process P1
    }
    return NULL;
}

int main() {
    pthread_t thread_0, thread_1;

    // Create threads for process P0 and P1
    pthread_create(&thread_0, NULL, process_0, NULL);
    pthread_create(&thread_1, NULL, process_1, NULL);

    // Join threads (this makes the main function wait for threads to finish)
    pthread_join(thread_0, NULL);
    pthread_join(thread_1, NULL);

    return 0;
}
