/*
Expected Output:
8
*/

#include <stdio.h>

int fib(int n) {
    static int memo[20] = {0};
    if (n <= 1) return n;
    if (memo[n]) return memo[n];
    memo[n] = fib(n-1) + fib(n-2);
    return memo[n];
}

int main() {
    printf("%d\n", fib(6));
}
