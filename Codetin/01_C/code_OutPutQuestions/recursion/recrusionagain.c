/*
Expected Output:
10 5 2 1 1 2 5 10
*/

#include <stdio.h>

int foo(int n) {
    printf("%d ", n);
    if (n > 1) foo(n / 2);
    printf("%d ", n);
}

int main() {
    foo(10);
}
