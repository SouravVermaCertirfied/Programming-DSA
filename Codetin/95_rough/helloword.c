#include <stdio.h>
#include <pthread.h>

// Function for the first thread
void* print_hello(void* arg) {
    printf("Hello ");
    return NULL;
}

// Function for the second thread
void* print_world(void* arg) {
    printf("World!\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create the first thread to print "Hello "
    if (pthread_create(&thread1, NULL, print_hello, NULL) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    // Wait for the first thread to finish execution
    pthread_join(thread1, NULL);

    // Create the second thread to print "World!\n"
    if (pthread_create(&thread2, NULL, print_world, NULL) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // Wait for the second thread to finish execution
    pthread_join(thread2, NULL);

    return 0;
}