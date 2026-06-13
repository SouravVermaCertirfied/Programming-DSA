## Thread vs Prcocess

Threads vs processes, race vs data race, deadlock/livelock/starvation, Coffman conditions, critical sections

| Concept       | Thread                  | Process                |
| ------------- | ----------------------- | ---------------------- |
| Memory        | Shared address space    | Separate address space |
| Creation      | Cheap                   | Expensive              |
| Communication | Shared memory           | IPC                    |
| Failure       | Can crash whole process | Isolated               |

> Threads are fast but dangerous due to **data race**.

## Race Condition
Race condition occurs when:
1. Multiple threads access shared data, where atleast one is write.
2. Outcome depends on execution timing.

## Race condition example
- The below function being called by two threads:  
- Here the expected out is 100, 
but due to race condition, actual output will be unpredictable.
> Becuase `counter++` is actually a **non-atomic** operation, it involves **load-add-store**. So, if the thread is pre-empted in between these operations there can be a race condition.
```c
int counter = 0;
void *fun(void *args){
    for(int i=0; i<100; i++)
        counter++;
}
```

## Fixing this Data Race Condition
1. Using mutex - the critical data is put inside the mutex lock.
2. Using atomic - the critical data increment is done using atomic operation.

1️⃣ **Using Mutex**
```c
#include<pthread.h>
#include<stdio.h>

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // ☢️

void *fun(void *args){
    for(int i=0;i <100 ; i++){
        pthread_mutex_lock(&lock); // ☢️
        counter++;
        pthread_mutex_unlock(&lock); // ☢️
    }
    return NULL;
}

int main(){
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, fun, NULL);
    pthread_create(&t2, NULL, fun, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("The output is : %d", counter);
    
    pthread_mutex_destroy(&lock); // ☢️
    return 0;
}
```

2️⃣ **Using Atomic** - Atomic was brought in C11
```c
#include<stdatomic.h> // for atomic functions
#include<pthread.h>
#include<stdio.h>

atomic_int counter;

void *fun(void *args){
    for(int i=0; i<100; i++){
        atmoic_fetch_add(&counter, 1); // ☢️
        // counter++; this syntax can also be used
    }
    return NULL;
}

int main(){
    pthread_t t1, t2;

    atomic_init(&counter, 0);

    pthread_create(&t1, NULL, fun, NULL);
    pthread_create(&t2, NULL, fun, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("counter value is: %d", atmoic_load(&counter)); //☢️ output is 100 * 2 = 200, since two threads
    printf("counter value is: %d", counter); //this sytax is also valid

    pthread_mutex_destroy(&lock);

    return 0;
}
```


## Data Race vs Race Condition
| Aspect                 | Race Condition            | Data Race                         |
| ---------------------- | ------------------------- | --------------------------------- |
| Scope                  | General concurrency bug   | Language-level memory model issue |
| Requires shared memory | ❌ No                      | ✅ Yes                             |
| Requires threads       | ❌ No                      | ✅ Yes                             |
| Result                 | Incorrect behavior        | **Undefined behavior**            |
| Fix                    | Ordering, synchronization | Mutexes or atomics                |

## Mutex vs Atomic
Golden Rule : Use atomic for states and atomic for relationships.
| Question                   | Mutex  | Atomic |
| -------------------------- | ------ | ------ |
| Protect multiple variables | ✅      | ❌      |
| Blocking                   | Yes    | No     |
| Overhead                   | Higher | Lower  |
| Complex invariants         | ✅      | ❌      |

---
<p align="left"><a href="00_QuestionBank.md">← 00_QuestionBank.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="11_Deadlocks.md">11_Deadlocks.md →</a></p>