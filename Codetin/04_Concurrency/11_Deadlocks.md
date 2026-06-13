# Deadlock
### What is deadlock ?
Deadlock occurs when a set of threads **permanently** block each other, because each thread is **holding** a resouce and **waiting** for a resouce held by another thread.

## Conditions for Deadlock (Coffman's 4 Conditions)
- All 4 Coffman Conditions should be simulaneously occuring for a deadlock to happen.
- To break the deadlock, we break atleast one of the conditions.

| # | Condition        | Meaning                                             |
| - | ---------------- | --------------------------------------------------- |
| 1 | Mutual Exclusion | Resource can be held by only one thread             |
| 2 | Hold and Wait    | Thread holds one resource while waiting for another |
| 3 | No Preemption    | Resource can’t be forcibly taken                    |
| 4 | Circular Wait    | Closed chain of threads waiting on each other       |

## Example
Below example illustrates a deadlocking C pogram.  
Here, 
- the `thread1` locks `lock_A` and goes to sleep
- so `thread2` starts `lock_B` and goes to sleep
- now when both `thread1` and `thread2` wake up, they are waiting and trying to lock a mutex that is already locked by someone else.
```c
pthread_mutex_t lock_A;
pthread_mutex_t lock_B;

void *thread1(void *args){
    pthread_mutex_lock(&lock_A);
    usleep(1000); // unistd.h
    pthread_mutex_lock(&lock_B);
    // critical section
    pthread_mutex_unlock(&lock_B);
    pthread_mutex_unlock(&lock_A);

    return NULL;
}

void *thread2(void *args){
    pthread_mutex_lock(&lock_B);
    usleep(1000); // unistd.h
    pthread_mutex_lock(&lock_A);
    // critical section
    pthread_mutex_unlock(&lock_A);
    pthread_mutex_unlock(&lock_B);

    return NULL;
}
```

## Fixing the deadlock using by breaking one Coffman's condition at a time
| Approach                | Coffman Condition Broken | Technique Used          |
| ----------------------- | ------------------------ | ----------------------- |
| 1️⃣ Lock ordering       | Circular wait            | Global ordering         |
| 2️⃣ Acquire-all-or-none | Hold and wait            | `trylock + retry`       |
| 3️⃣ Forced release      | No preemption            | Preemptive unlock       |
| 4️⃣ Lock-free           | Mutual exclusion         | Atomics / shared access |

### 1️⃣ Break Circular Wait
Enforce global lock order, so that all the threads aquire mutex in the same order.

```c
void* thread1(void* arg) {
    pthread_mutex_lock(&A);
    pthread_mutex_lock(&B);

    // critical section

    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&A);
    pthread_mutex_lock(&B);

    // critical section

    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);
    return NULL;
}

```

### 2️⃣ Break hold and wait
- A thread should try to lock all the resouces at once, or release everything and retry.
- **Try to lock both, if second fails, relesae both.**

```c
void *thread1(void *args){
    while(1){
        pthread_mutex_lock(&A);

        if(pthread_mutex_trylock(&B) == 0 ){ // lock aquired
            // critical section
            pthread_mutex_unlock(&A);
            pthread_mutex_unlock(&B);
            break;
        }
        pthread_mutex_unlock(&A);
    }
    return NULL;
}

// similar for thread2
```
### 3️⃣ Break No Preemption
- **Give up lock if the second lock cannot be aquired.**
- This is different from #2 conceptually: the system forces release when progress can’t be made.
    - #2 does not aquire lock B until is is available.
    - #3 gives up lock of A if B is not aquired
    - see the placement of the critical section and content of if block.

```c
void *thread1(void *args){
    while(1){
        pthread_mutex_lock(&A);

        if(pthread_mutex_trylock(&B) != 0 ){ // could not aquire lock
            pthread_mutex_unlock(&A);
        }
        else{
            // critical section
            pthread_mutex_unlock(&A);
            pthread_mutex_unlock(&A);
            break;
        }
    }
    return NULL;
}
// similar for thread2
```

### 4️⃣ Break Mutual Exclusion
**Remove exclusive access by using lock-free or shared mechanisms.** Like usage of atomic.
```c
#include <stdatomic.h>

atomic_int shared_resource;

void* thread1(void* arg) {
    atomic_fetch_add(&shared_resource, 1);
    return NULL;
}

void* thread2(void* arg) {
    atomic_fetch_add(&shared_resource, 1);
    return NULL;
}

```

---
<div style="display: flex; justify-content: space-between;">
    <a href="10_ThreadVsProcess.md">← 10_ThreadVsProcess.md</a>
    <a href="12_PriorityInversion.md">12_PriorityInversion.md →</a>
</div>