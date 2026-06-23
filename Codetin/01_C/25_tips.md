## 1. Bit Manipulation Tip

Subtle but common issue is shifting a 1 into the most significant bit (MSB) of a signed integer:
```c
int x = 1 << 31; // Undefined behavior
```
**Why is this a problem?**  
`int` is `signed`. Shifting 1 into the sign bit is undefined behavior according to the C standard.  
The code may compile without warnings, but at runtime it can produce unpredictable results—wrong values, crashes, or silent errors.  
✅ Correct approach: use unsigned integers for shifts that may reach the MSB:
```c
unsigned int x = 1U << 31; // Safe and well-defined
```

### Default Values struct
- you CANNOT initilize the default values for a `struct` in C.
- you CAN initilize the default values for a `struct` in CPP. Only for C++ v11 plus.
- you class you can always do it in, ofcorse in CPP.

---

## 2. Static variable in header file
What happens you make a `static` variable  in a `.h` and that header file is included in two `.c` files.

Short answer: **it compiles, but it is usually *not correct design*** unless you explicitly want separate copies per translation unit.

### What actually happens

When you write this in a header file:

```c
static int a = 10;
```

and include `h1.h` in both `c1.c` and `c2.c`, the preprocessor effectively copies it into both files, so you get:

- In `c1.c`: a **separate `static` variable `a`**
- In `c2.c`: another **separate `static` variable `a`**

### Key point: `static` at file scope means *internal linkage*

So each `.c` file gets its **own private version** of `a`.

They are:

- not shared
- not the same variable
- completely independent

So:

```c
// in c1.c
a = 20;

// in c2.c
printf("%d", a); // still 10
```

### Is it “correct”?

Depends on intent:

### ✔️ Correct if you want:

- Each `.c` file to have its own private `a`
- No sharing between translation units

### ❌ Usually incorrect if you want:

- A **single global variable shared across c1.c and c2.c**

In that case, this is wrong because you are unintentionally creating duplicates.

### Correct way to share a global variable

In the header (`h1.h`):

```c
extern int a;
```

In exactly one `.c` file (e.g., `c1.c`):

```c
int a = 10;
```

### Rule of thumb

- `static` in header → **one copy per .c file**
- `extern` in header + definition in one .c → **one shared global variable**

If you want, I can also explain why putting non-`static` definitions in headers causes linker errors (very common exam topic).


# 3. De- Morgan's Law

**De Morgan's Laws** are rules for transforming logical expressions involving `AND` and `OR`.

### The two laws

#### 1. Negation of AND

```text
!(A && B)  ==  (!A || !B)
```

Meaning:

> "Not (A and B)" is equivalent to "Not A or Not B"

Example:

```c
if (!(x > 0 && y > 0))
```

can be rewritten as:

```c
if (x <= 0 || y <= 0)
```

---

#### 2. Negation of OR

```text
!(A || B)  ==  (!A && !B)
```

Meaning:

> "Not (A or B)" is equivalent to "Not A and Not B"

Example:

```c
if (!(x == 0 || y == 0))
```

can be rewritten as:

```c
if (x != 0 && y != 0)
```

---

### Truth table intuition

For:

```text
!(A && B)
```

The result is true whenever at least one of `A` or `B` is false.

That's exactly:

```text
!A || !B
```

---

### Common firmware/embedded use

Suppose you have:

```c
if (!(rx_ready && tx_ready))
{
    return ERROR;
}
```

Using De Morgan:

```c
if (!rx_ready || !tx_ready)
{
    return ERROR;
}
```

Many engineers find the second version easier to read.

---

### Easy way to remember

When moving the `!` inward:

1. Flip every condition.
2. Swap `&&` and `||`.

Example:

```text
!(A && B && C)
```

becomes:

```text
!A || !B || !C
```

and

```text
!(A || B || C)
```

becomes:

```text
!A && !B && !C
```

This comes up surprisingly often in firmware code reviews because simplifying complex conditionals improves readability and reduces bugs.


---
<p align="left"><a href="25_tips2.md">← 25_tips2.md</a></p>
<p align="right" style="margin-top:-2.4em;"></p>