/*==========================================================
 Q2: Bitfields and Endianness
==========================================================*/
/*
Question:
Predict the output on little-endian and big-endian systems.
Expected Output (little-endian): 0x8D
Explanation:
- struct bitfield packing is compiler dependent.
- a=5 (3 bits), b=17 (5 bits) → memory byte: 10001101 = 0x8D
- Do not use bitfields for hardware register mapping across compilers.
*/
#include <stdio.h>

int main() {
    struct {
        unsigned a:3;
        unsigned b:5;
    } s = {5, 17};
    unsigned char *p = (unsigned char*)&s;
    printf("0x%02X\n", *p);
    return 0;
}
