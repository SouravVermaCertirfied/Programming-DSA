# DSA Notes and Tips

1. **Hamming distance**: 
    - Hamming distance is the no of bits that are different in two integers. 
    - Expected Approch is to do the **XOR** of both int, and count the no of set bits.
2. **Total Hamming Distance**:
    - In this hamming distance need to found, for all the numbers present in the array.
    - Expected Approch: 
        - For each bit position, count how many numbers have a 1 and how many have a 0.
        - The contribution of that bit position to the total Hamming distance is `count_ones × count_zeros`.
        - The final answer is the sum of these contributions across all bit positions.

3. Remove lowest set bit (Brian Kernighan’s Algorithm)
```c
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while(n){
            n = n & (n - 1);  // removes lowest set bit
            ans++;
        }
        return ans;
    }
};
```