/*
Expected Output:
1101
*/

#include <stdio.h>

void printBits(unsigned int n) {
    if (n == 0) return;
    printBits(n >> 1);
    printf("%d", n & 1);
}

int main() {
    printBits(13);
}
