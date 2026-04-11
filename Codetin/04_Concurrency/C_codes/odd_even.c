

#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

int counter = 0;
int turn = 2; // 2 is producer, 1 is odd, 0 is even
int finished = 0; 

void *consumer_odd(void *args){
    while(1){
        pthread_mutex_lock(&lock);
        while(!finished && !(turn==1)){
            pthread_cond_wait(&cond, &lock);
        }
        
        /* ☢️ CRITICAL FIX: Even if finished is true, if it's my turn to print (turn == 1), 
           I MUST print before I leave! Otherwise, I skip the last odd number.
        */
        if(finished && turn != 1){ 
            pthread_cond_broadcast(&cond); // ☢️ Wake up the other consumer so they aren't left sleeping
            pthread_mutex_unlock(&lock);
            break;
        }
        
        printf("Odd says : %d \n", counter);
        turn = 2;
        pthread_cond_broadcast(&cond); // ☢️ MISTAKE FIX: Must signal back to the producer to continue
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *consumer_even(void *args){
    while(1){
        pthread_mutex_lock(&lock);
        while(!finished && !(turn==0)){
            pthread_cond_wait(&cond, &lock);
        }
        
        /* ☢️ CRITICAL FIX: Even if finished is true, if it's my turn to print (turn == 0), 
           I MUST print before I leave! This ensures number 100 is never skipped.
        */
        if(finished && turn != 0){
            pthread_cond_broadcast(&cond); // ☢️ Wake up the other consumer so they can see finished=1 too
            pthread_mutex_unlock(&lock);
            break;
        }
        
        printf("Even says : %d \n", counter); // ☢️ MISTAKE FIX: Was labeled "Odd says" before
        turn = 2;
        pthread_cond_broadcast(&cond); // ☢️ MISTAKE FIX: Must signal producer to wake up
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *producer(void *args){
    /* ☢️ MISTAKE FIX: Changed from i <= 100 to i < 100. 
       Since we start at i=0 and do counter += 1, this gives us exactly 1 to 100.
    */
    for(int i=0; i<100; i++){
        pthread_mutex_lock(&lock);
        while(turn!=2){
            pthread_cond_wait(&cond, &lock);
        }
        counter += 1;
        turn = counter & 1;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_lock(&lock);
    finished = 1;
    pthread_cond_broadcast(&cond); // ☢️ MISTAKE FIX: Must broadcast after setting finished to wake stuck consumers
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    pthread_t odder, evener, giver;
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_create(&odder, NULL, &consumer_odd, NULL);
    pthread_create(&evener, NULL, &consumer_even, NULL);
    pthread_create(&giver, NULL, &producer, NULL);
    
    pthread_join(odder, NULL);
    pthread_join(evener, NULL);
    pthread_join(giver, NULL);
    
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    
    return 0;
}