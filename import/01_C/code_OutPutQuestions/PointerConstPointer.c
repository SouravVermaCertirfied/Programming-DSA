#include <stdio.h>

int main() {
    int val = 10;
    const int *p = &val;  // pointer to const int
    // *p = 20; // ❌ Not allowed - value is read-only via p
    printf("%d\n", *p);   // prints 10
    return 0;
}
