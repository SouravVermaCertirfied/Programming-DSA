### Question 1:
The Task: You are given a pointer to a memory-mapped register at address 0x40001000. You need to set bits 4, 5, and 6 to the binary value 101 (5) without disturbing any other bits in that 32-bit register.
Write the C code snippet to do this.
Follow-up: Why must the pointer be declared as volatile uint32_t*?

<details><summary>Solution</summary>

```c
// 1. Create a mask for bits 4, 5, and 6 (binary 111 is 0x7)
// 0x7 << 4 creates 0111 0000 in binary (bits 4, 5, 6 are set)
uint32_t mask = (0x7U << 4);

// 2. Prepare the value 101 (5) shifted to position 4
uint32_t value = (0x5U << 4);

// 3. Clear the bits using AND NOT (~mask), then set them using OR (| value)
*ptr = (*ptr & ~mask) | value;
```
</details>

### Question 2:
Write a macro to swap the nibbles in a 16-bit word. Example: 0x1234 becomes 0x2143.
<details><summary>Solution</summary>

```c
// APPROCH 1
#define SWAP_NIBBLES_16(x) ( ((x & 0xF0F0U) >> 4) | ((x & 0x0F0FU) << 4) )

// APPROCH 2
#define SWAP_NIBBLES_16(x) ( \
    ((x & 0x000FU) << 4)  | \
    ((x & 0x00F0U) >> 4)  | \
    ((x & 0x0F00U) << 4)  | \
    ((x & 0xF000U) >> 4)    \
)

#include <stdio.h>
#include <stdint.h>

// Macro to swap nibbles in a 16-bit word

int main() {
    uint16_t a = 0x1234;
    uint16_t b = SWAP_NIBBLES_16(a);

    printf("Original: 0x%04X\n", a); // 0x1234
    printf("Swapped:  0x%04X\n", b); // 0x2143

    return 0;
}

```
</details>

### Question 3:
Endianness Swap
The Task: Convert a 32-bit integer from Little Endian to Big Endian (or vice versa). This is essentially swapping the byte order: ABCD becomes DCBA.
<details><summary>Solution</summary>

```c
```
</details>

### Question 4:
Reverse the Bits
The Task: Given a 32-bit unsigned integer, reverse the order of the bits. Bit 0 becomes Bit 31, Bit 1 becomes Bit 30, and so on.
<details><summary>Solution</summary>

```c
```
</details>