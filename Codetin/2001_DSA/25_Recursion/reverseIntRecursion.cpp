#include<stdio.h>
#include<stack>
using namespace std;

int reversesUsingWhile(int num){ // using while loop
    int ans = 0;
    while(num){
        ans = ans * 10;
        ans = ans + num%10;
        num = num / 10;
    }
    return ans;
}

int reverseUsingRecursionSimple(int num, int ans){ // simple recursive approch - EXTRA parameter
    if(num==0)
        return ans;
    return reverseUsingRecursionSimple(num/10, (ans*10) + (num%10));
}

int reverserUsingRecursion(int num){ // 
    if(num<10)
        return num;
    return reverserUsingRecursion(num/10)*10 ;
}

int reverseUsingStackDS(int num){
    stack<int> stk;
    while(num){
        stk.push(num%10);
        num=num/10;
    }
    while(!stk.empty()){
        ans = stk.top();
        temp
        stk.pop();
    }
    return ans;
}

int main(){
    int num = 1023;
    printf("reversesUsingWhile : %d \n",reversesUsingWhile(num));
    printf("reverseUsingRecursionSimple : %d \n",reverseUsingRecursionSimple(num,0));
    printf("reverserUsingRecursion : %d \n",reverserUsingRecursion(num));
    printf("reverseUsingStackDS : %d \n",reverseUsingStackDS(num));
    return 0;
}