#include<stdio.h>

unsigned int reverseBits(unsigned int num){
    unsigned int ans = 0;
    for(int i=0; i<32; i++){
        ans = ans | (1 & num);
        ans = ans<<1;
        num = num>>1;
    }
    return ans;
}

int main(){
    unsigned int num = 0xAAAAFFFF;
    printf("Before : %X , After : %X", num, reverseBits(num));
    return 0;
}