/*
Expected Output:
3 2 1 1 2 3
*/

#include <stdio.h>

void printPattern(int n) {
    if (n == 0) return;
    printf("%d ", n);
    printPattern(n - 1);
    printf("%d ", n);
}

int main() {
    printPattern(3);
}
