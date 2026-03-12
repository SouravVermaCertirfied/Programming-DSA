#include <stdio.h>

/* Problem: Unset the rightmost set bit
   Approch: Using shift and bitwise AND
   TC : O(1)            SC: O(1)   */

int findPos(int n){
    int pos = -1;
    while(n){
        pos++;
        if ( n & 1 ) return pos;
        else n = n>>1;
    }
    return pos;
}

int unsetBitForPos(int n, int pos){
    int mask = 0x01;
    if(pos > -1){
        mask = mask << pos;
    }
    mask = ~mask;
    n = n & mask;
    return n;
}

int main(){
    int in = 2  ;
    printf("%d", unsetBitForPos(in,findPos(in)));
    return 0;
}