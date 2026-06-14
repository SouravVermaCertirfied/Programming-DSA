## 1. Complex Type Reading
Decode this expression often found in OS kernels:

```c
void (*signal(int sig, void (*func)(int)))(int);
```

**Explanation:**
This declares a function named `signal`.  
- `signal` takes two parameters:
    - sig: an `int`.
    - func: a function pointer that takes an `int` and returns `void`.
- `signal` returns a function pointer that takes an `int` as an argument and returns `void`.

## 2. Array pointer

In the below code, which line is wrong (if any):  

```c
int arr[10] = {0};
int *ptr = &arr;
ptr++; // line 1
arr++; // line 2
```
In the snippet, the 2 is wrong because arr is a `const` pointer to an `int`, hence cannot be incremented.

## 3. The Sneaky String Literal Pointer

```c
#include <stdio.h>

int main() {
    char *str = "Hello";
    x: 
    printf("%c", *str++);
    if(*str) goto x;
    return 0;
}
```

**Output:** `Hello`

* **Why:** `*str++` is parsed as `*(str++)` due to postfix operator precedence.
* It passes the current character to `printf`, and *then* increments the pointer to the next character.
* The `if(*str)` condition checks if the current character is the null terminator (`\0`). If it isn't, the `goto` loops it back. This is just a highly convoluted, low-level loop to print a string.

## 4. The `printf` Reversals

```c
#include <stdio.h>

int main() {
    int i = 1;
    printf("%d %d %d\n", i, ++i, i++);
    return 0;
}

```

**Output:** **Undefined / Compiler Dependent** (Often `3 3 1` on GCC)

* **Why:** Arguments to a function call (`printf`) can be evaluated in **any order** by the compiler.
* Most modern compilers evaluate arguments from **right to left**.
1. `i++` is evaluated first: returns `1`, then `i` becomes `2`.
2. `++i` is evaluated next: `i` becomes `3`, returns `3`.
3. `i` is evaluated last: returns `3`.

Because this relies on unspecified evaluation order combined with side effects, it technically triggers undefined behavior.

## 5. The Multi-Dimensional Pointer Confusion

```c
#include <stdio.h>

int main() {
    int a[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int (*ptr)[4] = a;
    printf("%d, %d\n", **ptr, **(ptr + 2));
    printf("%d\n", *(*(ptr + 1) + 2));
    return 0;
}

```

**Output:**

```text
1, 9
7
```

* **Why:** `ptr` is a pointer to an array of 4 integers.
* `ptr` points to the very first element, which is `1`.
* `ptr + 2` moves the pointer forward by *two entire rows* (2 * 4 integers). Dereferencing it twice (`(ptr + 2)`) gives the first element of the third row, which is `9`.
* `*(ptr + 1)` points to the second row. Adding `+ 2` to that moves it 2 integers forward into that row (pointing to `7`). Dereferencing it yields `7`.


---
<p align="left"><a href="09_Pointers.md">← 09_Pointers.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="11_Structure.md">11_Structure.md →</a></p>