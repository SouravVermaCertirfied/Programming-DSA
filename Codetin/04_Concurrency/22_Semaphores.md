# 1. Semaphores
A Semaphore is simply a variable (integer) used to control access to a shared resource by multiple processes in a concurrent system. It ensures that only the allowed number of processes can use a resource at a given time.
> A semaphore represents the availability of a finite number of identical resources. Threads block when no resources are available and wake when one is released.
```c
sem_t &sema;  // declaration

// there is NO extra line for init

sem_wait(&sema);   // P operation
/*  Decrements the counter
    Blocks if the counter becomes negative  */

sem_post(&sema);   // V operation
/*  Increments the counter
    Wakes a waiting thread if any exist */

sem_destroy(&sema); // destroy
```
# 2. Binary Semaphores
- It can have only two values 0 or 1.
- It looks like a mutex --- but it is not!

> A binary semaphore enforces exclusion, but it does not enforce ownership. That’s why it’s not a mutex.

| Feature                  | Mutex           | Binary Semaphore |
| ------------------------ | --------------- | ---------------- |
| Ownership                | Yes             | No               |
| Unlock by another thread | ❌               | ✅                |
| Priority inheritance     | Often supported | ❌                |
| Error detection          | Strong          | Weak             |

# 3. Counting Semaphores
- A counting semaphore represents N identical resources.
- Initial value = number of available resources.

| Aspect            | Semaphore | Cond Var    |
| ----------------- | --------- | ----------- |
| State             | Counter   | None        |
| Remembers signals | Yes       | No          |
| Ownership         | No        | Yes (mutex) |
| Expressiveness    | Lower     | Higher      |
| Risk              | Higher    | Lower       |

> For complex invariants, mutexes and condition variables are safer.

# 4. Code Example - Binary Semaphore
Mutual Exclusion without ownership.  
**Use Case**:  
    - Multiple threads increment a shared counter.  
    - Only one thread at a time may enter critical section.

**Context (Problem Statement)**
- We have multiple worker threads that all need to update a shared variable.
- The update operation is not atomic, so if two threads execute it concurrently, we’ll get a race condition.
- The requirement is:
        - Only one thread can enter the critical section at a time
        - Other threads must block, not spin
This is a mutual exclusion problem

```c

#define WORKERS (5u)

#include<pthread.h>
#include<stdio.h>



int main(){
    pthread_t p[];
    return 0;
}
```

## Counting Sempaphore Example
```c
/* implement tasks waiting in a queue to get access of the resource
    =======>>> GAMING PORTAL <<<=========
    ========COUNTING SEMAPHORES==========
    this is setup for gaming portal:
    - there are only 4 servers
    - and total 17 customers (gamers)
    - one server can only be used by one gamer at once
    
    ====this is not best approch to solve such problem====
    limitations of this example:
        - no fairness - no gaurentee that the task that came first will be served first
        - NO actual queue implementation - it working only based on the count of the semaphores.
        - It may behave like queue but there is NO queue implemented in this code.
*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h> // for sleep()
#include<stdlib.h>
#include<semaphore.h>

sem_t server_sem;

#define GAMERS (10u)
#define SERVERS (2u)

int value;

void *server(void *args){
    int *iptr = (int *)args;
    
    //sem_getvalue(&server_sem, &value); // OPTIONAL GET VALUE AND PRINTING
    //printf(" [%d] waiting.\t Servers Available : %d\n",*iptr, value);
    sem_wait(&server_sem);
    sem_getvalue(&server_sem, &value);
    //printf(" [%d] allocated.\t Servers Available : %d\n",*iptr, value);
    sleep(rand() % 5 + 1); // simulating gaming time
    sem_post(&server_sem);
    //sem_getvalue(&server_sem, &value);
    //printf(" [%d] exited.\t Servers Available : %d\n",*iptr, value);
    free(args);
    return NULL;
}

int main(){
    pthread_t p[GAMERS];
    sem_init(&server_sem, 0, SERVERS); 
    // (semaphore, 0 if only 1 process using it, semaphore intial value)
    for(int i=0; i<GAMERS; i++){
        int *val = (int *)malloc(sizeof(int));
        *val = i;
        pthread_create(&p[i], NULL, server, val);
    }
    for(int i=0; i<GAMERS; i++)
        pthread_join(p[i], NULL);
    
    sem_destroy(&server_sem);
    return 0;
}

```

---
<div style="display: flex; justify-content: space-between;">
    <a href="21_ConditionVariables.md">← 21_ConditionVariables.md</a>
    <a href="24_SemphoresVsMutex.md">24_SemphoresVsMutex.md →</a>
</div>