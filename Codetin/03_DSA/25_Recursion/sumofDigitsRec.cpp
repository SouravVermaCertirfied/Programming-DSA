#include<stdio.h>
#include<stack>
using namespace std;

int sumdigit(int num, int ans){
    if(num==0)
        return ans;
    return sumdigit(num/10, ans+num%10);
}

int sumdigits(int num){
    if(num==0)
        return num;
    return (num%10) + sumdigits(num/10);
}

int sumdigitw(int num){
    int ans = 0;
    while(num){
        ans = ans + num%10;
        num = num / 10;
    }
    return ans;
}

int main(){
    int num = 1023;
    printf("reversesUsingWhile : %d \n",reversesUsingWhile(num));
    printf("reversesUsingWhile : %d \n",reversesUsingWhile(num));
    printf("reverseUsingStackDS : %d \n",reverseUsingStackDS(num));
    return 0;
}