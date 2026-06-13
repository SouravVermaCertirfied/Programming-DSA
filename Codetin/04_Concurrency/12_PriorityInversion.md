# Priority Inversion
- Priority inversion occurs when a high priority task is **blocked waiting** due to for a resource that is held by a lower-priority-task.

**L M H** are jobs of low, medium and high priority.

### Senario 1 (only tasks L and H)
- Sequence of events:
> 1. **L** enters the locks and enters the critical section.
> 2. **H** comes, it gets the CPU as it is high priority, and hence the **L** is pre-empted.
> 3. Now, the **H** although has the CPU it is waiting for the **L** to release the lock for the critical section so that **H** can complete its work.

- Now, let us assume that so solve the first senario, we make a rule, that the **H** will not block any **L** that uses the critical section. 
- Even, with this attempt there can be caes of priority inversion, check below.

### Senario 2 (three tasks L, M and H)
- Sequence of events:
> 1. **L** starts aquires mutex.
> 2. **M** comes pre-empt **L** and starts working.
> 3. **H** comes blocks **M** but since the mutex is locked by **L**, **H** cannot complete its work.



## Exmaple in C
<details><summary>In the below example L blocks the `mutex` and H keeps waiting for the access.</summary>

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* low_priority_task(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Low-priority thread: acquired mutex, working...\n");
    sleep(5); // Simulate long work
    printf("Low-priority thread: releasing mutex\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* high_priority_task(void* arg) {
    sleep(1); // Let low-priority thread acquire mutex first
    int count = 1;
    while(1){ // added to keep trying
        printf("High-priority thread: trying to acquire mutex attempt : %d\n",count);
        count++;
        if(pthread_mutex_trylock(&mutex) == 0){
          //high priority task got access
          pthread_mutex_unlock(&mutex);
          printf("High-priority thread: released mutex\n");
          break;
        }
    }
    
    
    return NULL;
}

int main() {
    pthread_t low, high;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&low, NULL, low_priority_task, NULL);
    pthread_create(&high, NULL, high_priority_task, NULL);

    pthread_join(low, NULL);
    pthread_join(high, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

```
**Output**
```js
High-priority thread: trying to acquire mutex attempt : 4337
Low-priority thread: releasing mutex
High-priority thread: trying to acquire mutex attempt : 4338
High-priority thread: released mutex
```
</details>

## Types of Priority Inversion
1. **Bounded Priority Inversion** : Bounded priority inversion occurs when a high-priority task is delayed by a lower-priority task holding a resource. The delay is predictable and limited to the time the lower-priority task holds the resource.
2. **Unbounded Priority Inversion** : Unbounded priority inversion occurs when a medium-priority task (M) preempts L while it holds the lock. This action delays L from releasing the resource, which in turn delays H. The delay H experiences becomes unpredictable and can potentially be indefinite, hence the term "unbounded."

# Solutions to Priority Inversion
1. **Priority Inheritance**: Temporarily elevates the priority of the low-priority task holding the resource to match that of the highest-priority waiting task, ensuring timely resource release . 
> **L** inherits the priority of **H** while it is executing the critical section used by both.

2. **Priority Ceiling Protocol**: Assigns a maximum priority to each resource, preventing tasks with lower priorities from acquiring resources needed by higher-priority tasks .

3. **Avoiding Blocking**: Utilizes non-blocking algorithms or designs systems to minimize shared resource usage, thereby reducing the chances of priority inversion .

---
<p align="left"><a href="11_Deadlocks.md">← 11_Deadlocks.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="20_Mutex.md">20_Mutex.md →</a></p>