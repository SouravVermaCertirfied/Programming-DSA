#include <stdio.h>
#include <pthread.h>
#include <conio.h>   // for getch()

// Thread function
void* threadFunc(void* arg) {
    int id = *(int*)arg;
    printf("Hello from thread %d!\n", id);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // Create threads
    pthread_create(&t1, NULL, threadFunc, &id1);
    pthread_create(&t2, NULL, threadFunc, &id2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads finished.\n");

    getch(); // pause console
    return 0;
}