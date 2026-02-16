# Thread-Safe Counting: Local vs Shared Counter in Loop Condition

## 1. Using a local variable in each thread (safe)

```c
void *fun(void *args) {
    for(int i = 0; i < 100; i++) {
        atomic_fetch_add(&counter, 1);
    }
}
```
- Each thread tracks its own i.
- Loop runs exactly the intended number of times per thread.
- Shared counter updates are atomic → final total is exact. ✅
- Key: Local loop counters are independent, so no race occurs in the loop itself.

## 2. Using the shared counter in the loop condition (can overshoot)

```c
void *fun(void *args) {
    while(counter < 65000) { // 🐞 incorrect usage of <
        // < operator is not atomic hence, will lead to
        // inderministic cases
        counter++; // atomic increment
    }
}
```
Loop condition reads the shared counter, accessed by multiple threads simultaneously.  
Example of overshoot:
```js
Thread 1 reads counter = 64999
Thread 2 reads counter = 64999
Both increment → counter = 65001

```
Even though counter++ is atomic, the check (counter < 65000) + increment is not atomic, so overshoot occurs.

Key: Using the shared counter as a loop limiter is risky in multithreaded loops.


Local loop counters = predictable per-thread execution.  
Shared counter as loop condition = may overshoot, because check + increment is not atomic.

### Fix for the overshoot case
```c
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_int counter = 0;

void *fun(void *args) {
    while (1) {
        if (current >= 65000) break; //☢️
        int current = atomic_fetch_add(&counter, 1); //☢️
        
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;

    pthread_create(&p1, NULL, fun, NULL);
    pthread_create(&p2, NULL, fun, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("The final value of counter : %d\n", atomic_load(&counter));

    return 0;
}

```