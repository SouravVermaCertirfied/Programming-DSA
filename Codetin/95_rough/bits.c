#include<stdio.h>
#include<conio.h>

int main(){
    int number = 0x5A5A5A5A;
    unsigned int input  = (unsigned int)number;
    unsigned int rev = 0;

    for(int i=0 ; i<32; i++){
        rev = rev<<1;
        rev |= number&1;
        number = number>>1;
        
    }
    printf("%x", rev);
    getch();
    return 0;
}