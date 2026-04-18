Tips :  
- Use U suffixes: Always use 1U << n to ensure you are working with unsigned integers.   
- Think about "Power of 2": Many bit problems are solved by realizing that $(n \text{ \& } (n-1)) == 0$ checks if a number is a power of 2.
- Fixed Width Types: Use uint32_t or uint16_t instead of int to show you understand embedded constraints.


## Problem 1 : Sparse Bit Count & Manipulation
Scenario: 

Part A: Write a function to determine if a number is Sparse. A number is sparse if no two bits in its binary representation are adjacent (e.g., 5 (101) is sparse, but 6 (110) is not).

Part B: Given a non-sparse number, find the next smallest sparse number greater than it.

<details><summary>Answers</summary>  

Part A: Checking for SparsityThe most efficient way to check for adjacency is using the bitwise AND operator with a shifted version of the number itself.  

Logic: If we have a number $n$, and we perform $n \text{ \& } (n >> 1)$, the result will be non-zero if there are any adjacent '1' bits.  

```c
bool isSparse(uint32_t n) {
    // If (n & (n >> 1)) is 0, no two 1s are adjacent
    return !(n & (n >> 1));
}
```

Part B:  
Finding the Next Sparse NumberThis is where the  difficulty kicks in. A naive approach (incrementing by 1 and checking) is too slow for real-time systems.  

The Strategy: 
- Scan the number from left to right (MSB to LSB) to find the first occurrence of two adjacent set bits (11).Suppose the 11 starts at index $i$. 
- To make the number sparse and larger:Add 1 to the bit at index $i$.Set all bits to the right (less significant) of index $i$ to 0.
- Repeat the check until no adjacent bits remain.
- Example Walkthrough ($n = 6$):Binary: 0110 (Indices: 3 2 1 0)Adjacent 11 found at indices 2 and 1.
- Add 1 at index 2 $\rightarrow$ 1000 (which is 8).8 is sparse. Return 8.

```c
uint32_t nextSparse(uint32_t n) {
    // We use a vector or a temporary representation to track changes
    // Or we can process bit-by-bit
    uint32_t res = n;
    int last_final_bit = 0;

    for (int i = 0; i < 31; i++) {
        // Check if current bit and next bit are both 1
        if (((res >> i) & 1) && ((res >> (i + 1)) & 1)) {
            
            // 1. Add 1 to the next bit position to clear the adjacency
            res += (1 << i);
            
            // 2. All bits to the right of this change must become 0 
            // to find the SMALLEST next sparse number.
            for (int j = i; j >= last_final_bit; j--) {
                res &= ~(1 << j);
            }
            
            // Optimization: Keep track of how far we've cleared
            last_final_bit = i;
        }
    }
    return res;
}
```
</details>

## Problem 2 : Convert Big-Endian to Little-Endian or vice versa

Scenario:   

Part A: Write a function to reverse the byte order of a 32-bit unsigned integer (Convert Big-Endian to Little-Endian or vice versa).  

Part B: From the resulting value, extract the bits from position $j$ to $i$ (inclusive) and return them as a standalone integer.

<details><summary>Answers</summary>  
Part A: Byte Reversal (Endian Swap)
To swap bytes, we use masks to isolate each 8-bit chunk, shift them to their new positions, and combine them using the bitwise OR operator.

Logic:

Byte 0 (bits 0-7) moves to Byte 3 (bits 24-31).

Byte 1 (bits 8-15) moves to Byte 2 (bits 16-23).

...and so on.

```c
uint32_t swapBytes(uint32_t n) {
    return ((n >> 24) & 0x000000FF) | // Move byte 3 to byte 0
           ((n >> 8)  & 0x0000FF00) | // Move byte 2 to byte 1
           ((n << 8)  & 0x00FF0000) | // Move byte 1 to byte 2
           ((n << 24) & 0xFF000000);   // Move byte 0 to byte 3
}
```

Part B: Extracting a BitfieldExtracting bits between $i$ and $j$ (where $i \geq j$) requires creating a dynamic mask.Logic:Create a mask of $1$ s that is the length of the desired field: $(i - j + 1)$.  

Shift the original number right by $j$ so the desired field starts at bit 0.AND the shifted number with the mask.The Formula:$$\text{result} = (n >> j) \text{ \& } ((1 \ll (i - j + 1)) - 1)$$  

Note: Be careful with $(1 \ll 32)$ as it can cause overflow on 32-bit systems.

```c
uint32_t extractBits(uint32_t n, int i, int j) {
    // 1. Calculate number of bits to extract
    int num_bits = i - j + 1;
    
    // 2. Create a mask of 'num_bits' ones
    // Handling the 32-bit edge case safely:
    uint32_t mask = (num_bits == 32) ? 0xFFFFFFFF : (1U << num_bits) - 1;
    
    // 3. Shift and mask
    return (n >> j) & mask;
}
```
</details>

## Problem 3 : Bit Counting (Brian Kernighan’s)

Most efficient way to count the number of set bits (1s) in an integer.

Standard approach: Loop 32 times.  
Optimal approach: Only loop as many times as there are 1s.

<details><summary>Answers</summary>

Why n & (n - 1) works: Subtracting 1 from a number flips all bits after the rightmost set bit (including that bit itself). When you AND that with the original number, that specific 1 disappears.

```c
int countSetBits(uint32_t n) {
    int count = 0;
    while (n > 0) {
        // This magic expression clears the least significant set bit
        n &= (n - 1); 
        count++;
    }
    return count;
}
```
</details>

## Problem 4 : Check if a number is a power of two ?

Using only one line of code

<details><summary>Answers</summary>  

```c
bool isPowerOfTwo(uint32_t n) {
    return n && !(n & (n - 1));
}
```
</details>

## Problem 5 : The Bit-Reversal Permutation

Your Task: Write a function to reverse the actual bits of a 32-bit unsigned integer.

Input: `1011 0000 0000 0000 0000 0000 0000 0000`

Output: `0000 0000 0000 0000 0000 0000 0000 1101`

<details><summary>Answers</summary>  

Solution 1:  
```c
uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        // Pull the LSB of n and shift it to its new position
        result <<= 1;       // Make room for the next bit
        result |= (n & 1);  // Add the LSB of n
        n >>= 1;            // Move to the next bit of n
    }
    return result;
}
```

Solution 2: The Strategy:  
- Swap adjacent 1-bit chunks.  
- Swap adjacent 2-bit chunks.  
- Swap adjacent 4-bit chunks.  
- Swap adjacent 8-bit chunks (bytes).  
- Swap adjacent 16-bit chunks (half-words).  

```c
uint32_t reverseBitsOptimized(uint32_t n) {
    // 1. Swap odd and even bits
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
    
    // 2. Swap consecutive pairs (2 bits)
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
    
    // 3. Swap nibbles (4 bits)
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
    
    // 4. Swap bytes (8 bits)
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
    
    // 5. Swap half-words (16 bits)
    n = (n >> 16) | (n << 16);
    
    return n;
}
```