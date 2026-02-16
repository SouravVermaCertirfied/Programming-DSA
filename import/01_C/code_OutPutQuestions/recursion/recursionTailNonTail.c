/*
Expected Output:
15 15
*/

#include <stdio.h>

int tail(int n, int acc) {
    if (n == 0) return acc;
    return tail(n - 1, acc + n);
}

int nonTail(int n) {
    if (n == 0) return 0;
    return n + nonTail(n - 1);
}

int main() {
    printf("%d %d\n", tail(5, 0), nonTail(5));
}
