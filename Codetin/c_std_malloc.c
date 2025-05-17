#include<stdio.h>
#include<stdlib.h>

int main(){
    int size = 10;
    char *location = (char*)malloc(size);
    char *temp = location;
    printf("Malloc start -- \n");
    if(temp == NULL)
        //no memory allocated
    else{
        for(int i=0;i<size;i++){
            temp[i] = i;
            printf("%d ", temp[i]);
        }
    }
    printf("\n");

    int size2 = 40;
    int items = size2 / sizeof(int);
    int *location1 = (int*)malloc(size2);
    int *temp1 = location1;
    printf("Malloc start -- \n");
    for(int i=0;i<items;i++){
        temp1[i] = i;
        printf("%d ", temp1[i]);
    }
    printf("\n");


}