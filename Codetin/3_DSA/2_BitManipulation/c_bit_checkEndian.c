/*
Little-endian means that the least significant byte is stored first in memory (at the lowest address).
Big-endian means that the most significant byte is stored first in memory (at the lowest address).
*/

#include <stdio.h>

int main() {
    unsigned int num = 1;
    unsigned char *byte = (unsigned char*)&num;

    if (byte[0] == 1) {
        printf("This system is Little-endian\n");
    } else {
        printf("This system is Big-endian\n");
    }

    return 0;
}
