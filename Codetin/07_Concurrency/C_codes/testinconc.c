#include <stdio.h>
#include <pthread.h>
#include <stdio.h>

// Thread function
void* threadFunction(void* arg) {
    char* message = (char*)arg;  // cast void* back to char*
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Messages for threads
    char msg1[] = "Hello from Thread 1";
    char msg2[] = "Hello from Thread 2";

    // Create threads
    if (pthread_create(&thread1, NULL, threadFunction, (void*)msg1)) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, threadFunction, (void*)msg2)) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished.\n");
    getchar();
    return 0;
}
