//01_TwoThreads.c

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *myfunction(void *args){
    char *message = (char *)args;
    printf("%s\n",message);
    return NULL;
}
int main(){
    pthread_t t1, t2;

    pthread_create(&t1, NULL, myfunction, "t1 enter chat.\n");
    pthread_create(&t2, NULL, myfunction, "t2 enter chat.\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("End of program.");
    return 0;
}