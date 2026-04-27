#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *hello(void *args){
	sleep(2);
	printf("Hello ");
	return NULL;

}

void *world(void *args){ 
	sleep(1);
	printf("World "); 
	return NULL;
}

int main(){
	pthread_t t1, t2;
	pthread_create(&t1, NULL, hello, NULL);
	pthread_create(&t2, NULL, world, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}
