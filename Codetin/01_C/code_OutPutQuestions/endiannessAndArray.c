/*==========================================================
 Q9: Pointer Arithmetic and Endianness
==========================================================*/
/*
Question:
What does this print on little-endian vs big-endian?
Expected Output: 
- *(p+4) = first byte of second integer

(Little Endinan)
Offset: 0  1  2  3 | 4  5  6  7 | 8  9  10 11 | 12 13 14 15
Bytes: 11 11 11 11 | BB 22 22 AA | DD 33 33 CC | 44 44 44 44
So, if the system is little-endian output is 0xBB

(Big Endian)
Offset: 0  1  2  3 | 4  5  6  7 | 8  9  10 11 | 12 13 14 15
Bytes:  11 11 11 11 | AA 22 22 BB | CC 33 33 DD | 44 44 44 44
So, if the system is big-endian output is 0xAA
*/
#include <stdio.h>

int main() {
    unsigned int arr[4] = {0x11111111, 0xAA2222BB, 0xCC3333DD, 0x44444444};
    unsigned char *p = (unsigned char*)arr;
    printf("0x%X\n", *(p + 4)); 
    return 0;
}
