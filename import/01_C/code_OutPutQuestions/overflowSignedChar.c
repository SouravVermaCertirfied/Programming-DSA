#include <stdio.h>

int main() {
    char x = 128;  // this max for signed char
    x = x + 1;           // signed overflow -> undefined behavior
    printf("%d\n", x);   // often prints -127 (wraps around)
    return 0;
}
