/*
Expected Output:
7
*/

#include <stdio.h>

int f(int n) {
    if (n <= 2) return n - 1;
    return f(n - 1) + f(n - 2);
}

int main() {
    printf("%d\n", f(6));
}
