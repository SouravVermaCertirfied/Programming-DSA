# Problem statement

Print numbers from 1 to 100:
- If a number is divisible by 3, print "Fizz"  
- If a number is divisible by 5, print "Buzz"  
- If a number is divisible by both 3 and 5, print "FizzBuzz"  
- Otherwise print the number itself  

---

```c

#include <pthread.h>
#include <stdio.h>

int counter = 1;
const int N = 50;

pthread_mutex_t lock;
pthread_cond_t wakeall;

void* thread_A(void *arg)
{
while (1) {
pthread_mutex_lock(&lock);


    while (counter <= N &&
           !(counter % 3 == 0 && counter % 5 != 0))
        pthread_cond_wait(&wakeall, &lock);

    if (counter > N) {
        pthread_cond_broadcast(&wakeall);
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    printf("Fizz ");
    counter++;

    pthread_cond_broadcast(&wakeall);
    pthread_mutex_unlock(&lock);
}


}

void* thread_B(void *arg)
{
while (1) {
pthread_mutex_lock(&lock);


    while (counter <= N &&
           !(counter % 3 != 0 && counter % 5 == 0))
        pthread_cond_wait(&wakeall, &lock);

    if (counter > N) {
        pthread_cond_broadcast(&wakeall);
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    printf("Buzz ");
    counter++;

    pthread_cond_broadcast(&wakeall);
    pthread_mutex_unlock(&lock);
}


}

void* thread_C(void *arg)
{
while (1) {
pthread_mutex_lock(&lock);


    while (counter <= N &&
           !(counter % 3 == 0 && counter % 5 == 0))
        pthread_cond_wait(&wakeall, &lock);

    if (counter > N) {
        pthread_cond_broadcast(&wakeall);
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    printf("FizzBuzz ");
    counter++;

    pthread_cond_broadcast(&wakeall);
    pthread_mutex_unlock(&lock);
}


}

void* thread_D(void *arg)
{
while (1) {
pthread_mutex_lock(&lock);


    while (counter <= N &&
           (counter % 3 == 0 || counter % 5 == 0))
        pthread_cond_wait(&wakeall, &lock);

    if (counter > N) {
        pthread_cond_broadcast(&wakeall);
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    printf("%d ", counter);
    counter++;

    pthread_cond_broadcast(&wakeall);
    pthread_mutex_unlock(&lock);
}


}

int main()
{
pthread_t A, B, C, D;


pthread_mutex_init(&lock, NULL);
pthread_cond_init(&wakeall, NULL);

pthread_create(&A, NULL, thread_A, NULL);
pthread_create(&B, NULL, thread_B, NULL);
pthread_create(&C, NULL, thread_C, NULL);
pthread_create(&D, NULL, thread_D, NULL);

pthread_join(A, NULL);
pthread_join(B, NULL);
pthread_join(C, NULL);
pthread_join(D, NULL);

pthread_mutex_destroy(&lock);
pthread_cond_destroy(&wakeall);

printf("\n");
return 0;


}

```