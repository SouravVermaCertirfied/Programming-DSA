#include<stdio.h>

void printstring(char *st, int len){
    int i=0;
    while(i<len){
        printf("%c",st[i]);
        i++;
    }
    printf("\n");
}

// 1. revese the string in place
reverseArrayInPlace(char *st, int len){
    printstring(st, len);
    // the code
    int left = 0; 
    int right = len-1;
    while(left < right){
        char temp = st[left];
        st[left] = st[right];
        st[right] = temp;
        left++;
        right--;
    }
    printstring(st, len);
}


// 2. find the second largest element
void secondlargest(){
    int arr[5] = {5, 9, 6, 7, 1};
    int l = -1;
    int sl = -1;
    for( int i=0; i<5; i++){
        if(arr[i] > l){
            sl = l;
            l = arr[i];
        }
    }
}

int main(){
    char name[] = "rohan";
    reverseArrayInPlace(name, 5);
}