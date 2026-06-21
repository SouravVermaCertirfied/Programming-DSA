Here are **Top 25 Qualcomm-style Bit Manipulation Coding Questions with concise solutions (C/C++)**. These are the **most frequently tested patterns** in interviews.

---

# 🧠 TOP 25 BIT MANIPULATION QUESTIONS (WITH SOLUTIONS)

---

## 1. Check if number is power of 2

```cpp
bool isPowerOf2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}
```

---

## 2. Count set bits

```cpp
int count(int n) {
    int c = 0;
    while (n) n &= (n - 1), c++;
    return c;
}
```

---

## 3. Find single number (others twice)

```cpp
int single(vector<int>& a){
    int x = 0;
    for (int v : a) x ^= v;
    return x;
}
```

---

## 4. Missing number 0..n

```cpp
int missing(vector<int>& a){
    int x = 0, i = 0;
    for (int v : a) x ^= v ^ i++;
    return x ^ i;
}
```

---

## 5. Swap two numbers without temp

```cpp
a ^= b;
b ^= a;
a ^= b;
```

---

## 6. Check ith bit set

```cpp
bool check(int n, int i){
    return (n >> i) & 1;
}
```

---

## 7. Set ith bit

```cpp
n |= (1 << i);
```

---

## 8. Clear ith bit

```cpp
n &= ~(1 << i);
```

---

## 9. Toggle ith bit

```cpp
n ^= (1 << i);
```

---

## 10. Remove lowest set bit

```cpp
n &= (n - 1);
```

---

## 11. Isolate lowest set bit

```cpp
int lb = n & -n;
```

---

## 12. Two unique numbers (others twice)

```cpp
vector<int> two(vector<int>& a){
    int x = 0;
    for(int v: a) x ^= v;

    int mask = x & -x;
    int a1=0,b1=0;

    for(int v: a){
        if(v & mask) a1 ^= v;
        else b1 ^= v;
    }
    return {a1,b1};
}
```

---

## 13. Reverse bits (32-bit)

```cpp
unsigned int rev(unsigned int n){
    unsigned int r=0;
    for(int i=0;i<32;i++)
        if(n & (1u<<i))
            r |= (1u<<(31-i));
    return r;
}
```

---

## 14. Power of 4 check

```cpp
bool isPow4(int n){
    return n>0 && !(n&(n-1)) && (n%3==1);
}
```

---

## 15. Multiply by 2 / divide by 2

```cpp
n << 1; // *2
n >> 1; // /2
```

---

## 16. Find XOR from 1 to n

```cpp
int xor1ToN(int n){
    if(n%4==0) return n;
    if(n%4==1) return 1;
    if(n%4==2) return n+1;
    return 0;
}
```

---

## 17. Bit difference between two numbers

```cpp
int diff(int a,int b){
    return __builtin_popcount(a^b);
}
```

---

## 18. Check opposite signs

```cpp
bool opposite(int a,int b){
    return (a^b) < 0;
}
```

---

## 19. Absolute value using bits

```cpp
int abs(int n){
    int m = n >> 31;
    return (n ^ m) - m;
}
```

---

## 20. Count trailing zeros

```cpp
int tz(int n){
    return __builtin_ctz(n);
}
```

---

## 21. Count leading zeros

```cpp
int lz(int n){
    return __builtin_clz(n);
}
```

---

## 22. Find MSB position

```cpp
int msb(int n){
    return 31 - __builtin_clz(n);
}
```

---

## 23. Generate all subsets

```cpp
for(int mask=0; mask<(1<<n); mask++){
    for(int i=0;i<n;i++)
        if(mask&(1<<i)) cout<<arr[i];
}
```

---

## 24. Check if number is sparse (no adjacent 1s)

```cpp
bool sparse(int n){
    return !(n & (n >> 1));
}
```

---

## 25. Flip bits to convert A → B

```cpp
int flips(int a,int b){
    return __builtin_popcount(a^b);
}
```

---

# ⚡ How Qualcomm typically tests this

They combine:

* XOR + masking
* edge cases (negative, overflow)
* optimization (O(1) tricks)
* reasoning, not memorization

---