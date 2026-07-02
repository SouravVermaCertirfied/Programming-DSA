/*
You can use global variables
Each task should have
    - the function that the task must execute
    - the address of next task
Have on task queue, you can use linked list
    enqueue from the rear
    dequeue from the front
Define N as the totoal number of threads
Define worker_thread function that is reusable to execute one task after another
Define work_fun - function that does the actual work for the given task
Use appropriate locks for synch :
    - lock
    - cond
*/

/* THIS IS A MYSELF WRITTEN CODE */

#include<stdio.h>
#include<stdbool.h>
#include<pthread.h>
#include<stdlib.h>

#define N 10 // no of threads
#define T 100 // no of tasks



typedef struct task_t{
    void (*work_fun_var)(task_t *, int);
    int task_id;
    struct task_t *next;
} task_t;

void* submit_thread_fun(void *args);
void *worker_thread_fun(void *args);
void work(task_t *task, int thread_id);

pthread_t thread_objs[N];
pthread_t submit_thread_obj;
bool keeprunning;

task_t *front, *rear;

pthread_mutex_t lock;
pthread_cond_t cond;

void threadPool_init(){
    front = NULL;
    rear = NULL;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    keeprunning = true;
    static int thread_ids[N];
    pthread_create(&submit_thread_obj, NULL, submit_thread_fun, NULL );
    for(int i=0; i<N; i++){
        thread_ids[i] = i;
        pthread_create(&thread_objs[i], NULL, worker_thread_fun, &thread_ids[i]);
    }
    return;
}

void threadPool_destroy(){

    for(int i=0; i<N; i++){
        pthread_join(thread_objs[i], NULL);
    }
    pthread_join(submit_thread_obj, NULL);
    pthread_mutex_destroy(&lock); // ☢️☢️☢️ join threads and then destroy locks
    pthread_cond_destroy(&cond);
    return;

    
}

void enq(int task_id){
    task_t *newtask = (task_t *)malloc(sizeof(task_t));
    newtask->next = NULL;
    newtask->task_id = task_id;
    newtask->work_fun_var = work;
    // if any val the add here
    if(rear==NULL){ // first item
        front = newtask;
        rear = newtask;
    }
    else{
        rear->next = newtask;
        rear = newtask;
    }
    return ;
}

task_t* deq(){
    if(front==NULL){ // no items in the queue
        return NULL;
    }
    task_t *temp = front;
    if(front==rear)
        rear = NULL;
    front = front->next;
    return temp;
}

void* submit_thread_fun(void *args){
    for(int i=0; i<T; i++){
        pthread_mutex_lock(&lock);
        enq(i);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    pthread_mutex_lock(&lock);
    keeprunning = false;
    pthread_cond_broadcast(&cond); // first signal/broadcast then release mutex lock
    pthread_mutex_unlock(&lock);
    return NULL;
}

void work(task_t *task, int thread_id){
    printf("The thread %d, is executing task : %d. \n", thread_id, task->task_id);
    return;
}

void *worker_thread_fun(void *args){
    int *thread_id = (int *)args;
    while(1){
        pthread_mutex_lock(&lock);
        while(keeprunning && front==NULL){  // ABC
            pthread_cond_wait(&cond, &lock); 
        }
        if(keeprunning==false && front==NULL){ // XYZ ☢️☢️☢️ Exit check happnes after waking up!
            pthread_mutex_unlock(&lock);      // ABC line check should be before XYZ
            return NULL;
        }
        task_t *stolentask = deq();
        pthread_mutex_unlock(&lock);
        stolentask->work_fun_var(stolentask, *thread_id);
        free(stolentask);
    }
    return NULL;
}



int main(){
    threadPool_init();

    threadPool_destroy();
    printf("Exiting with Grace, bybye!");
    return 0;
}