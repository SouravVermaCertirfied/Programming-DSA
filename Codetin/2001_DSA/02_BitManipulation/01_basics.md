### Question 1: Set Specific Bits
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

### Question 2: Swap Nibble
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

### Question 3: Endienss Conversion
Endianness Swap
The Task: Convert a 32-bit integer from Little Endian to Big Endian (or vice versa). This is essentially swapping the byte order: ABCD becomes DCBA.
<details><summary>Brute</summary>

```c

uint32_t swapEndiannessBrute(uint32_t n) {
    // Treat the memory location of n as an array of 4 individual bytes
    uint8_t *bytes = (uint8_t *)&n;
    uint8_t temp;

    // Swap element 0 (Byte 1) and element 3 (Byte 4)
    temp = bytes[0];
    bytes[0] = bytes[3];
    bytes[3] = temp;

    // Swap element 1 (Byte 2) and element 2 (Byte 3)
    temp = bytes[1];
    bytes[1] = bytes[2];
    bytes[2] = temp;

    return n;
}

```
</details>

<details><summary>Optimal</summary>

```c

uint32_t swapEndianness(uint32_t n) {
    return ((n >> 24) & 0x000000FF) | // Move byte 4 to byte 1
           ((n >> 8)  & 0x0000FF00) | // Move byte 3 to byte 2
           ((n << 8)  & 0x00FF0000) | // Move byte 2 to byte 3
           ((n << 24) & 0xFF000000);  // Move byte 1 to byte 4
}

```
</details>

### Question 4: Reverse Bits
Reverse the Bits
The Task: Given a 32-bit unsigned integer, reverse the order of the bits. Bit 0 becomes Bit 31, Bit 1 becomes Bit 30, and so on.
<details><summary>Brute</summary>

```c

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        // Shift result left to make room, then bring in the last bit of n
        result = (result << 1) | (n & 1);
        // Shift n right to move to the next bit
        n >>= 1;
    }
    return result;
}

```

* **Time Complexity:** $O(1)$ (Always loops exactly 32 times).
* **Space Complexity:** $O(1)$.

---

</details>

<details><summary>Optimal</summary>

**Method 2: The Divide & Conquer Approach (Highly Optimized)**

```c

uint32_t reverseBitsOptimized(uint32_t n) {
    // 1. Swap adjacent single bits (0101... and 1010...)
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
    
    // 2. Swap adjacent 2-bit pairs (0011... and 1100...)
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
    
    // 3. Swap adjacent 4-bit nibbles (00001111...)
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
    
    // 4. Swap adjacent 8-bit bytes
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
    
    // 5. Swap adjacent 16-bit half-words
    n = (n >> 16) | (n << 16);
    
    return n;
}

```

* **Time Complexity:** $O(1)$ (Executes in exactly 5 steps, completely bypassing the 32-iteration loop).
* **Space Complexity:** $O(1)$.

</details>


### Question 5: Extract the value.  

The Task: 


<details><summary>Solution</summary>

```c

```

</details>

### Question 6: Toggle the value

The Task: 

<details><summary>Solution</summary>

```c

```

</details>

### Question 7: Check bit

The Task: 

<details><summary>Solution</summary>

```c

```

</details>

### Swap two numbers using XOR without temp variable.

### Why XOR of same numbers cancels out?

### bit masking
Bit masking & manipulation  
What is a bitmask and why is it used?  
How to generate all subsets using bitmask?  
How to check subset using bitwise operations?  
How to clear all bits from LSB to ith bit?  
How to set all bits from 0 to ith position?  

### Shifts & arithmetic tricks
Multiply a number by 2 using bit shift?  
Divide a number by 2 using bit shift?  
Why left shift may cause overflow?  
Difference between n << 1 and n * 2?  
Why right shift of negative numbers is     implementation-dependent?  

### Advanced bit hacks
How to reverse bits of a number?  
How to swap odd and even bits?  
How to find position of only set bit?  
How to detect if two numbers have opposite signs?  
How to compute absolute value using bit tricks?  

### Counting & math with bits
How to count trailing zeros?  
How to count leading zeros?  
How to find MSB (most significant bit)?  
How to compute log base 2 using bits?  
Why powers of 2 are important in memory alignment?  

### Interview-level coding patterns
How to check if ith bit is set in array of integers?
How to find duplicate using bitwise operations?
How to compute XOR of range 1 to n?
How to find bit difference between two numbers?
How to minimize flips to convert A to B?

### Edge cases & traps  
What happens when shifting by >= word size?  
Why ~x behaves differently in signed integers?  
What is sign extension in bit operations?  
Why INT_MIN is tricky in absolute value?  
How to avoid undefined behavior in bit hacks?  