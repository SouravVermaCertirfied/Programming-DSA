# Endianess

Endianness defines the order in which a processor stores multi-byte data (like 16-bit, 32-bit, or 64-bit integers) in memory.
- If the MCU’s endianness doesn’t match the peripheral, data must be byte-swapped. Reading/writing multi-byte numbers in flash, EEPROM, or SD cards may require careful byte ordering.
- It is a convection deciding what is stored in the **lowest byte in memory**:
    - If the lowerst byte stores **MSB** then **Big**
    - --------------------------- **LSB** ---- **Little**   
- Eg: `1991994` is `0x 001E 653A`

<img src="https://uynguyen.github.io/Post-Resources/Endian/Endian-Overview.png" alt="My Image" style="max-width: 500px; height: auto;">

### Simple Program to detect Endiness

```c
#include <stdio.h>

int main() {
    unsigned int x = 0x12345678;
    unsigned char *c = (unsigned char*)&x;

    if (*c == 0x78)
        printf("Little-endian\n");
    else
        printf("Big-endian\n");

    return 0;
}

```

### Simple Program with array
```c
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


```

