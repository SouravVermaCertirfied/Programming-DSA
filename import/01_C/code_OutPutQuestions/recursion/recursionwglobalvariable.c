/*
Expected Output:
64
*/

#include <stdio.h>

int g = 1;

int fun(int n) {
    if (n == 0) return 0;
    g = g * n;
    return fun(n - 1) + g;
}

int main() {
    printf("%d\n", fun(4));
    return 0;
}
