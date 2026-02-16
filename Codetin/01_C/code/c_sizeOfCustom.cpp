#include<stdio.h>

/*Idea is to create a null pointer and make an array increment of 1 and then substract with 0th item to get size*/
#define custom_sizeOf(type) (char*)(&(((type*)0)[1])) - (char*)(&(((type*)0)[0]))

int main(){
    int a = 10;
    int b;
    // cout<<custom_sizeOf(a);
    // cout<<custom_sizeOf(b);
    printf("%d\n",custom_sizeOf(int));
    printf("%d\n",custom_sizeOf(char));
    printf("%d\n",custom_sizeOf(double));
    return 0;
}