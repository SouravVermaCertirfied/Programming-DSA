#include <stdio.h>

/* Problem: Set the Kth bit
   Approch: 
   TC :             SC:    */

int setKthBit(int n, int k){
    int mask = 1<<k;
    n = n | mask;
    // one liner 
    // return ((1<<k)|n);
    return n;
}

int main() {
    printf("%d", setKthBit(5,1));
    return 0;
}