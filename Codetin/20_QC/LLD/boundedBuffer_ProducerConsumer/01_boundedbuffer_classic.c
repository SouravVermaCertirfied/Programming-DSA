#include<stdio.h>
#include<pthread.h>

int buff[16]; // it can acutally store 15 bytes only
int head = 0; // exits from here
int tail = 0; // enters from here
int size = 16;

pthread_mutex_t lock; // mutex to lock the buffer
pthread_cond_t readytoread; // singal the cosumerer to awake
pthread_cond_t readytowrite; // singal to producer to awake

void initlocks(){
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&readytoread, NULL);
    pthread_cond_init(&readytowrite, NULL);
}

void destroylocks(){
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&readytoread);
    pthread_cond_destroy(&readytowrite);
}


bool isFull(){
    if(((tail+1)%size) == head)
        return true;
    return false;
}

bool isEmpty(){
    if(head==tail)
        return true;
    return false;
}

void enqueu(int item){
    buff[tail]=item;
    tail = (tail+1)%size;
}

int dequeue(){
    int item = buff[head];
    head = (head+1)%size;
    return item;
}

void *produce_thread(void *args){
    int k = 1;
    while(k<100){
        pthread_mutex_lock(&lock);
        while(isFull()){
            pthread_cond_wait(&readytowrite, &lock);
        }
        printf("pushing k : %d\n", k);
        enqueu(k);
        pthread_cond_signal(&readytoread);
        pthread_mutex_unlock(&lock);
        k++;
    }
    return NULL;
}

void *consume_thread(void *args){
    int k = 1;
    while(k<100){
        pthread_mutex_lock(&lock);
        while(isEmpty()){
            pthread_cond_wait(&readytoread, &lock);
        }
        int item = dequeue();
        printf("poping item : %d\n", item);
        pthread_cond_signal(&readytowrite);
        pthread_mutex_unlock(&lock);
        k++;
    }
    return NULL;
}

int main(){
    pthread_t producer, consumer;

    initlocks();
    
    pthread_create(&producer, NULL, produce_thread, NULL);
    pthread_create(&consumer, NULL, consume_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    destroylocks();

    return 0;
}