/*
Expected Output:
14
*/

#include <stdio.h>

int funB(int n);
int funA(int n) {
    if (n <= 1) return 1;
    return n + funB(n - 1);
}
int funB(int n) {
    if (n <= 1) return 1;
    return n + funA(n / 2);
}

int main() {
    printf("%d\n", funA(6));
}
