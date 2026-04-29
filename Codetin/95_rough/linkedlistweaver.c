/*
    Implement a Linked List weaver:
        There are 5 threads that should simulaneously BUILD the linked list until 100 nodes are added
        There are 5 threads that should simulaneously CLEAR the linked list until 100 nodes are added
        There is just one head
        Use pthread
        building and clearing order follows of FIFO
*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>


#define MAX_NODES 200U

typedef struct Node{
    int val;
    struct Node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;
int counter = 1;

pthread_mutex_t lock;

void *builders(void *args){
    int *id = (int *)args;
    while(1){
        int usec = rand() % 100001; 
        usleep(usec);
        pthread_mutex_lock(&lock);
        if(counter<=MAX_NODES){
            Node *temp = (Node*)malloc(sizeof(Node));
            temp->val = counter;
            printf("Builder [%d] Counter : %d built.\n", *id, counter);
            temp->next = NULL;
            counter++;

            if(head==NULL){
                head = temp;
                tail = temp;
            }
            else{
                tail->next = temp;
                tail = temp;
            }
        }
        else{
            break;
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *cleaners(void *args){
    int *id = (int *)args;
    while(1){
        int usec = rand() % 100001; 
        usleep(usec);
        pthread_mutex_lock(&lock);
        if(head != NULL){
            Node *temp = head;
            printf("Cleaner [%d] : Counter : %d cleaned.\n", *id, head->val);
            if(tail==head) tail = NULL;
            head = head->next;
            free(temp);
        }
        else{
            if(counter>=MAX_NODES){
                break;
            }
            printf("Builders are so slow, waiting for the kill !!\n");
        }
        pthread_mutex_unlock(&lock);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    printf("Starting the linked list chaos\n");
    
    pthread_mutex_init(&lock, NULL);

    pthread_t b[5];
    pthread_t c[5];

    for(int i=0; i<5; i++){
        int *bid = (int *)malloc(sizeof(int));
        int *cid = (int *)malloc(sizeof(int));
        *bid = i; 
        *cid = i;
        pthread_create(&b[i], NULL, builders, bid);
        pthread_create(&c[i], NULL, cleaners, cid);
    }

    for(int i=0; i<5; i++){
        pthread_join(b[i], NULL);
        pthread_join(c[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("The end");
    return 0;
}