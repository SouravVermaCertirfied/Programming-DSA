# Condition Variables

- A condition variable does two things:
    - Release the mutex and sleep the thread.
    - Wake up the thread, when the shared condition is true.  
- It is always used along with a mutex.

**Synatx in C**
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
<div style="display: flex; justify-content: space-between;">
    <a href="20_Mutex.md">← 20_Mutex.md</a>
    <a href="22_Semaphores.md">22_Semaphores.md →</a>
</div>