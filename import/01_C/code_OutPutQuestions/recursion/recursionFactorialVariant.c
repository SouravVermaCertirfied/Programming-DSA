/*
Expected Output:
22
*/

#include <stdio.h>

int fact(int n) {
    static int c = 1;
    if (n == 0) return 1;
    c++;
    return n * fact(n - 1) + c;
}

int main() {
    printf("%d\n", fact(3));
    return 0;
}
