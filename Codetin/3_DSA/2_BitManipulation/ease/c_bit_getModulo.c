#include <stdio.h>

/* Problem: Given two numbers n and d where d is a power of 2 number, 
            the task is to perform n modulo d without the division and modulo operators.
   Approch: 
            The idea is to leverage bit manipulation for modulo operations when the divisor is a power of 2. 
            Since any power of 2 has exactly one bit set, subtracting 1 from it gives a number with all bits to 
            the right of that bit set. 
            This creates a bit mask that, when combined with the bitwise AND operation, 
            effectively performs the modulo operation without division.

            This approach works because when we perform n % d where d is 2^k, 
            we’re essentially extracting the k least significant bits of n. 
            For example, n % 4 is equivalent to getting the last 2 bits of n. 
   TC :             SC:    */

int getModulo(int n, int k){
    int mask = (k-1);
    return n & mask;
}

int main() {
    printf("%d", getModulo(12,8));
    return 0;
}