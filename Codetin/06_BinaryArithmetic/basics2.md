Binary subtraction using **two’s complement** is done by converting the subtraction into an addition problem:

> **A − B = A + (two’s complement of B)**

Then you simply perform binary addition.

Below is a clear step-by-step method with examples.

---

# 1. Core Idea

Instead of subtracting directly:

* Take the number to be subtracted (B)
* Find its two’s complement (i.e., −B)
* Add it to A

Discard any carry beyond the fixed bit width.

---

# 2. Step-by-step procedure

For A − B (using n bits):

### Step 1: Write A and B in binary (same bit width)

### Step 2: Find two’s complement of B

* Invert bits (1’s complement)
* Add 1

### Step 3: Add A + (two’s complement of B)

### Step 4: Ignore carry beyond n bits

### Step 5: Interpret result

---

# 3. Example 1: 7 − 5 (8-bit)

## Step 1: Convert to binary

* 7 = `00000111`
* 5 = `00000101`

---

## Step 2: Two’s complement of 5

### Invert bits:

```
00000101 → 11111010
```

### Add 1:

```
11111010 + 1 = 11111011
```

So:

* −5 = `11111011`

---

## Step 3: Add to 7

```
  00000111   (7)
+ 11111011   (−5)
------------
 100000010
```

---

## Step 4: Keep only 8 bits

```
00000010
```

---

## Step 5: Result

```
7 − 5 = 2
```

---

# 4. Example 2: 5 − 7 (negative result)

## Step 1:

* 5 = `00000101`
* 7 = `00000111`

---

## Step 2: Two’s complement of 7

Invert:

```
00000111 → 11111000
```

Add 1:

```
11111000 + 1 = 11111001
```

So:

* −7 = `11111001`

---

## Step 3: Add

```
  00000101   (5)
+ 11111001   (−7)
------------
  11111110
```

---

## Step 4: Interpret result

`11111110` is negative (MSB = 1)

Find magnitude:

### Invert:

```
11111110 → 00000001
```

### Add 1:

```
00000001 + 1 = 00000010
```

So magnitude = 2

---

## Final result:

```
5 − 7 = −2
```

---

# 5. Example 3: 9 − 12 (another negative case)

## Step 1:

* 9 = `00001001`
* 12 = `00001100`

---

## Step 2: Two’s complement of 12

Invert:

```
00001100 → 11110011
```

Add 1:

```
11110011 + 1 = 11110100
```

So −12 = `11110100`

---

## Step 3: Add

```
  00001001
+ 11110100
-----------
  11111101
```

---

## Step 4: Interpret

MSB = 1 → negative

Magnitude:

Invert:

```
11111101 → 00000010
```

Add 1:

```
00000010 + 1 = 00000011
```

So magnitude = 3

---

## Final result:

```
9 − 12 = −3
```

---

# 6. Key shortcut (important exam trick)

Instead of thinking “subtraction”:

> Always think: **Add negative using two’s complement**

So:

```
A − B = A + (~B + 1)
```

---

# 7. Overflow note (important concept)

In fixed-width systems (like 8-bit):

* If result exceeds range, it wraps
* Carry out is ignored

Example:

```
  11111111
+ 00000001
-----------
1 00000000 → result = 00000000
```

---

# 8. Why this works (intuition)

Two’s complement is designed so that:

* Adding a negative number behaves exactly like subtraction
* Hardware only needs one circuit (adder)

So subtraction is just:

> “flip + add + normal addition”

---

# 9. Quick summary

To compute A − B:

1. Convert A and B to binary
2. Find two’s complement of B
3. Add to A
4. Ignore extra carry
5. Read result (signed interpretation if needed)

---