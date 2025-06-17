#include <stdio.h>

/* Problem: Check if Kth Bit is set.
   Approch: 
   TC :             SC:    */

bool isKthBitSet(int n, int k){
    int mask  = 1<<k;
    return (bool)(n & mask);
}
int main() {
    printf("%d", isKthBitSet(5,2));
    return 0;
}