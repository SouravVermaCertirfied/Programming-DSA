#include<stdio.h>
#include<pthread.h>
#include<stdatomic.h>
#include<stdlib.h>

#define MAX_CONSUMERS 5
#define MAX_PRODUCERS 50

typedef struct tNode_t{
    int val;
    struct tNode_t *next;
}tNode_t;

typedef struct jobQueue_t{
    tNode_t *head;
    tNode_t *tail;
    int done;
} jobQueue_t;

_Atomic int total;

pthread_mutex_t qLock;
pthread_cond_t qCond;


void enQ(jobQueue_t *jQ, tNode_t *newNode){
	pthread_mutex_lock(&qLock);
	if(jQ->tail){
		jQ->tail->next = newNode;
	}
	else{
		jQ->head = newNode;
	}
	jQ->tail = newNode;
	pthread_cond_signal(&qCond); 
	pthread_mutex_unlock(&qLock);
}

void deQ(jobQueue_t *jQ){
	if( jQ->head == NULL){
		return;
	}
	else if(jQ->head == jQ->tail){
		free(jQ->head);
		jQ->head = NULL;
		jQ->tail = NULL;
	}
	else{
		tNode_t *temp = jQ->head;
		jQ->head = jQ->head->next; 
		free(temp);           
	}
	return;
}

void *consumer(void *args){
	jobQueue_t *jQ = (jobQueue_t *)args;
	
	while(1){
		pthread_mutex_lock(&qLock);
		while( jQ->head == NULL && jQ->done < MAX_PRODUCERS ){ 
			pthread_cond_wait(&qCond, &qLock); 
		}
		if( jQ->head == NULL && jQ->done >= MAX_PRODUCERS ){ 
			pthread_mutex_unlock(&qLock);
			break;
		}
		else{
			int tempval = jQ->head->val; 
			deQ(jQ); 
			pthread_mutex_unlock(&qLock);
			atomic_fetch_add(&total, tempval);
		}
	}
	return NULL;
	
}


void *producer(void *args){
	jobQueue_t *jQ = (jobQueue_t *)args;
	
	for(int i=0; i<100; i++){
		tNode_t *newNode = (tNode_t *)malloc(sizeof(tNode_t)); 
		newNode->val = i;
		newNode->next = NULL;
		enQ(jQ, newNode);
	}
	pthread_mutex_lock(&qLock);
	jQ->done += 1;	
	pthread_mutex_unlock(&qLock); 
	pthread_cond_signal(&qCond);
	return NULL;
}

int main(){
    pthread_t conThreadPool[MAX_CONSUMERS];
    pthread_t proThreadPool[MAX_PRODUCERS];
	
	pthread_mutex_init(&qLock, NULL);
	pthread_cond_init(&qCond, NULL);
	
	jobQueue_t jQ = {
		.head = NULL,
		.tail = NULL,
		.done = 0
	
	};
	
	atomic_init(&total, 0); 
	
	for(int i=0; i<MAX_CONSUMERS; i++) pthread_create(&conThreadPool[i], NULL, consumer, &jQ);
	for(int i=0; i<MAX_PRODUCERS; i++) pthread_create(&proThreadPool[i], NULL, producer, &jQ);
	
	for(int i=0; i<MAX_PRODUCERS; i++) pthread_join(proThreadPool[i], NULL);
	for(int i=0; i<MAX_CONSUMERS; i++) pthread_join(conThreadPool[i], NULL);
	
	// ⚠️ design issue: usually you join producers first, then consumers
	// otherwise consumers might wait forever depending on signaling logic
	
	pthread_mutex_destroy(&qLock);
	pthread_cond_destroy(&qCond);
	
	int temp = atomic_load(&total); 
	printf("The total sum value is : %d ", temp);
	
    return 0;

}