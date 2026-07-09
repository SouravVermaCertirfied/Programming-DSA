## Exchange bits

```cpp
#include<iostream>
using namespace std;

int exchanger(int val, int idx1, int idx2) {
    // 1. Extract the bits at idx1 and idx2 (0 or 1)
    int bit1 = (val >> idx1) & 1;
    int bit2 = (val >> idx2) & 1;

    // 2. If the bits are different, toggle both of them
    if (bit1 != bit2) {
        // Create a mask with 1s at idx1 and idx2
        unsigned int mask = (1U << idx1) | (1U << idx2);
        val ^= mask; // XOR flips 1 to 0 and 0 to 1
    }

    return val;
}


int exchanger(int val, int idx1, int idx2) {
    // Determine if the bits are different (will be 1 if different, 0 if same)
    int xor_bit = ((val >> idx1) ^ (val >> idx2)) & 1; // 

    // Shift that difference back to both idx1 and idx2 positions
    unsigned int mask = (xor_bit << idx1) | (xor_bit << idx2);

    // XORing with the mask will swap them if they were different, or do nothing if they were the same
    return val ^ mask;
}
//Even though the function signature uses signed int, using 1U (unsigned 1) for the bit-shifting is a safety measure. 
// If idx1 or idx2 is 31 (the sign bit), shifting a signed 1 into that position causes undefined behavior in older C++ standards. 
// 1U makes it completely safe.


```

## Reverse bits

```cpp
#include <iostream>
#include <bitset>
#include <cstdint> // Using fixed-width unsigned integers for safety

using namespace std;

// 1. Iteration Method
uint32_t byiternation(uint32_t val) {
    uint32_t ans = 0;
    int totalbits = sizeof(uint32_t) * 8;
    for (int i = 0; i < totalbits; i++) {
        ans = ans << 1;
        ans = ans | (val & 1);
        val = val >> 1; // Safe now because it's unsigned (fills with 0)
    }
    return ans;
}

// 2. Two-Pointer Swapping Method
uint32_t byswapingtwopointers(uint32_t val) {
    int l = 0;
    int r = (sizeof(val) * 8) - 1;

    while (l < r) {
        // Extract l and r-th bits
        uint32_t lbit = (val >> l) & 1;
        uint32_t rbit = (val >> r) & 1;
        
        // Update l and r-th bits
        val = (val & (~(1U << l))) | (rbit << l);
        val = (val & (~(1U << r))) | (lbit << r);
        l++;
        r--;
    }
    return val;
}

// 3. Optimal Divide and Conquer Method (Fixed Masks)
uint32_t byoptimalmethod(uint32_t val) {
    // Added 'U' suffix to hex constants to treat them as unsigned
    val = ((val & 0xFFFF0000U) >> 16) | ((val & 0x0000FFFFU) << 16);
    val = ((val & 0xFF00FF00U) >> 8)  | ((val & 0x00FF00FFU) << 8);
    val = ((val & 0xF0F0F0F0U) >> 4)  | ((val & 0x0F0F0F0FU) << 4);
    val = ((val & 0xCCCCCCCCU) >> 2)  | ((val & 0x33333333U) << 2);
    val = ((val & 0xAAAAAAAAU) >> 1)  | ((val & 0x55555555U) << 1);

    return val;
}

int main() {
    uint32_t val = 10; // Try changing this to a massive number like 4294967290 U to test
    const int BIT_SIZE = sizeof(val) * 8;

    cout << "Original: " << bitset<BIT_SIZE>(val) << "\n\n";

    cout << "Iteration: " << bitset<BIT_SIZE>(byiternation(val)) << "\n";
    cout << "Pointers:  " << bitset<BIT_SIZE>(byswapingtwopointers(val)) << "\n";
    cout << "Optimal:   " << bitset<BIT_SIZE>(byoptimalmethod(val)) << "\n";

    return 0;
}

```