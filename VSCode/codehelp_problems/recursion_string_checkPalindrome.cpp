#include<iostream>
#include<string.h>

using namespace std;

bool isPalindromeRecursion(char input[], int left, int right){

    if(left>=right){
        return true;
    }

    if(input[left]!=input[right]){
        return false;
    }

    isPalindromeRecursion(input,left+1,right-1);
}

bool isPalindromeRecursion(char input[], int size){
    
    return isPalindromeRecursion(input, 0, size-1);
}

int main(){
    char input[] = "mada1m";
    int size =  strlen(input);
    cout<<isPalindromeRecursion(input, size);
    return 0;
}