//02_Race Condition.c
/*
    - program to show race condition
    - two threads will count from 1 to 10
    - and try to accumulate the sum in a variable
    - lets see if the sum will come as excact 10 something else
*/
#include <stdio.h>
#include <pthread.h>

unsigned int counter = 0;
unsigned int sum = 0;

void* increment(void* arg) {
    for (int i = 0; i < 65000; i++) {
        counter++;  // race condition here
        sum += 1;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter = %d\n", counter);
}
