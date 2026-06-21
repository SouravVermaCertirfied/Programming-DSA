Below is a **C/C++ bit manipulation cheat sheet with code snippets for every major pattern**. Keep this as your rapid revision + interview reference.

---

# 🧠 1. Basic Bit Operations

```cpp
// Set ith bit
n = n | (1 << i);

// Clear ith bit
n = n & ~(1 << i);

// Toggle ith bit
n = n ^ (1 << i);

// Check ith bit
bool isSet = (n >> i) & 1;

// Odd / Even
bool even = (n & 1) == 0;
```

---

# ⚡ 2. Core Bit Tricks

```cpp
// Check power of 2
bool isPowerOf2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Remove lowest set bit
n = n & (n - 1);

// Isolate lowest set bit
int lowbit = n & (-n);

// Count set bits (Brian Kernighan)
int countBits(int n) {
    int cnt = 0;
    while (n) {
        n = n & (n - 1);
        cnt++;
    }
    return cnt;
}
```

---

# 🔁 3. XOR Patterns

```cpp
// Single number (all others twice)
int singleNumber(vector<int>& nums) {
    int x = 0;
    for (int v : nums) x ^= v;
    return x;
}

// Swap using XOR
a ^= b;
b ^= a;
a ^= b;

// Missing number (0..n)
int missingNumber(vector<int>& nums) {
    int x = 0, i = 0;
    for (int v : nums) x ^= v ^ i++;
    return x ^ i;
}
```

---

# 🧩 4. Two Unique Numbers (advanced XOR)

```cpp
vector<int> twoUnique(vector<int>& nums) {
    int x = 0;
    for (int v : nums) x ^= v;

    int mask = x & (-x); // rightmost set bit

    int a = 0, b = 0;
    for (int v : nums) {
        if (v & mask) a ^= v;
        else b ^= v;
    }
    return {a, b};
}
```

---

# 🔄 5. Shift Operations

```cpp
// Multiply / Divide by 2
int mul2 = n << 1;
int div2 = n >> 1;

// Check overflow risk (left shift)
if (n > (INT_MAX >> 1)) {
    // overflow will happen
}
```

---

# 🧮 6. Subsets using Bitmask

```cpp
vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;

    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i))
                subset.push_back(nums[i]);
        }
        res.push_back(subset);
    }
    return res;
}
```

---

# 🔢 7. Bit Counting Variants

```cpp
// Built-in (fastest)
int cnt = __builtin_popcount(n);

// Leading zeros
int lz = __builtin_clz(n);

// Trailing zeros
int tz = __builtin_ctz(n);
```

---

# 🔄 8. Reverse Bits

```cpp
unsigned int reverseBits(unsigned int n) {
    unsigned int res = 0;

    for (int i = 0; i < 32; i++) {
        if (n & (1u << i))
            res |= (1u << (31 - i));
    }
    return res;
}
```

---

# 🔀 9. Swap Odd-Even Bits

```cpp
int swapBits(int n) {
    int even = n & 0xAAAAAAAA;
    int odd  = n & 0x55555555;

    even >>= 1;
    odd <<= 1;

    return (even | odd);
}
```

---

# 📍 10. MSB / Log2 / Position

```cpp
// floor(log2(n))
int log2n(int n) {
    int res = 0;
    while (n >>= 1) res++;
    return res;
}

// MSB position
int msb(int n) {
    return log2n(n);
}
```

---

# ➕ 11. Absolute Value Trick

```cpp
int absBit(int n) {
    int mask = n >> 31;
    return (n ^ mask) - mask;
}
```

---

# ⚠️ 12. Edge Case Patterns

```cpp
// Avoid undefined shift
if (i >= 32) return 0;

// Safe power of 2 check
bool safePower2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

---