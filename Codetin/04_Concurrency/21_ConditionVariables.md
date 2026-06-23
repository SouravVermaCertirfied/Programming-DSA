# Condition Variables

### A condition variable does two things:
- Release the mutex and sleep the thread.
- Wake up the thread, when the shared condition is true.  

It is always used along with a mutex.

---
## Lost Wakeup
- Condition variables don't queue notifications; they only wake threads that are already waiting. The actual condition must be stored in shared state protected by a mutex.
- A condition variable is not a message queue. If pthread_cond_signal() occurs before a thread begins waiting, the signal is lost. Therefore, the actual state must be stored in a shared predicate protected by a mutex, and the waiting thread checks that predicate in a loop.

### Example of lost wakeup
```c
pthread_cond_signal(&cond);  // no waiter yet

// later
pthread_cond_wait(&cond, &mutex); // singal has already been done, so this guy will keep waiting forever, if there are no new `signals`
```

**If you need queued notifications**  Use something that maintains state/count, such as:
- POSIX semaphores (sem_t)  
- work queue protected by a mutex  
- Event counters / sequence numbers  

---

## Condition Varible Synatx in C
```cpp
pthread_mutex_t lock;
pthread_cond_t cond_var; ☢️ // declare
... 
pthread_cond_wait(&cv, &m); ☢️ // used in the thread that must go to sleep
...
pthread_cond_signal(&cv); // ☢️ used in the thread that singals wake up to the other thread
```

**Exmaple of Car-Tanker-Station**  
In this example:
    - The petrol station has a tank.
    - A tanker is filling the petrol station tank.
    - A car has come to refuel itself.

```c
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

pthread_mutex_t lock;
pthread_cond_t cond;

int stationLevel = 0;
int carFuel = 0;

void *carThread( void *args){

    pthread_mutex_lock(&lock);
    while(carFuel <= 40 ){
        printf("Car waiting at the station. \n");
        pthread_cond_wait(&cond, &lock);
        // Equivalent to:
        // pthread_mutex_unlock(&lock);
        // wait for signal on cond
        // pthread_mutex_lock(&lock)
    }
    carFuel -= 40;
    printf("Car fueling done. \n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *tankerThread(void *args){

    for(int i=0; i<5; i++){
        pthread_mutex_lock(&lock);
        carFuel += 15;
        printf("Tanker is filling station. \n");
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond);
        usleep(1);
    }
    return NULL;
}

int main(){
    pthread_t car;
    pthread_t tanker;
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&car, NULL, carThread, NULL);
    pthread_create(&tanker, NULL, tankerThread, NULL);

    pthread_join(car, NULL);
    pthread_join(tanker, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
```

---
<p align="left"><a href="20_Mutex.md">← 20_Mutex.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="22_Semaphores.md">22_Semaphores.md →</a></p>