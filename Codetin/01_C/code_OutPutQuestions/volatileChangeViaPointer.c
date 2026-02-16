/*==========================================================
 Q4: const volatile Combination
==========================================================*/
/*
Question:
Why might this print the original value even after a pointer write?
Expected Output: ABCD
Explanation:
- const → prevents modification via variable name
- volatile → reads from memory every time
- Writing through a pointer may be ignored (hardware register style)
*/
#include <stdio.h>

int main() {
    const volatile int reg = 0xABCD;
    int *p = (int*)&reg;
    *p = 0x1234;
    printf("%X\n", reg);
    return 0;
}
