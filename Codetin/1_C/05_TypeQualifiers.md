# Type Qualifiers

- They tell more info about how a variable can be **accessed** and **modified**.
- 4 types - `const` , `volatile` , `restrict` and `_Atomic`

> IMPORTANT

`const int` and `int const` are the SAME!  
Hence, the value.

## 🧠 **KEY IDEA**:

**In C, the const keyword applies to whatever is directly to its left — unless there’s nothing to the left, in which case it applies to what’s on the right.**

Hence, `const int const * ptr;` will give a syntax error, as both the const try to make the int leading to redduncy.

```c
   error: duplicate 'const'
      |     const int const *ptr;
      |               ^~~~~
      |               -----
```

## 1. `const`
1. How const affects pointer declarations differently ?  

`const` can apply either to the pointer itself or to the data it points to, which affects what can be modified.
- `const int *ptr;` — pointer to constant data; you cannot modify the data via ptr, but you can change the pointer itself.
- `int *const ptr;` — constant pointer to data; you cannot change the pointer (it always points to the same address), but you can modify the data.
- `const int *const ptr;` — constant pointer to constant data; neither the pointer nor the data it points to can be changed.

<hr>

***What if ? Take a global/local variable. Make it as a const. And then create a pointer that points to that variable. And try to modifiy the value using the pointer, what is the expected behaviour*** 

| Property          | Global `const var`                                             | Local `const var`                                         |
| ----------------- | -------------------------------------------------------------- | --------------------------------------------------------- |
| Storage           | Often placed in **read-only memory** (like `.rodata`)          | Usually placed on the **stack** (writable)                |
| Can you modify?   | Casting away `const` + modify → UB, may crash or ignore writes | Casting away `const` + modify → UB, may "work" but unsafe |
| Defined behavior? | No (undefined behavior)                                        | No (undefined behavior)                                   |

## 2. `volatile`
- Volatile tells the compiler that the variable can change anytime,  
hence it should not optimize it away.
- It is **guarantee** that the variable should be always read from the assinged memory.
- It should never be cached.
- 
```c
volatile int flag = 0;

void wait_for_flag() {
    while (!flag) {
        // without volatile, compiler might optimize this to an infinite loop
        // by assuming flag never changes inside this loop
    }
}
```

## 3. `restrict`
Using this keyword the developer tells the compiler that : “During this pointer’s lifetime, the object it points to will only be accessed through this pointer (and not through any other pointer).”
- This lets the compiler safely assume no aliasing, so it can reorder or vectorize memory operations.
- If you promise no aliasing using `restrict` but your pointers do alias, your program may behave unpredictably.  

This allows the compiler to optimize memory accesses aggressively, especially in loops and functions working on arrays, because it can assume no overlap between pointers.

Example:
```c
void add_array(int *restrict dest, const int *restrict src, int size){
    size--;
    while(size>=0){
        dest[size] = dest[size] + src[size];
    }
}
```
If a and b overlapped, the compiler would have to generate safer, possibly slower code.  
With restrict, it assumes they don't, enabling vectorization and other optimizations.

Tip
<details>
with and without `restrict` this si how the assembly would have changed.

without `restrict`
```asm
.L3:
    movl    (%rsi,%rax,4), %edx  # load b[i]
    addl    %edx, (%rdi,%rax,4)  # add to a[i]
    addq    $1, %rax
    cmpq    %rcx, %rax
    jne     .L3

```

with `restrict` (could be vectorized)
```asm
    # Uses AVX instructions to load, add and store 8 ints at a time
    vmovdqu ymm0, ymmword ptr [rsi + rax*4]
    vpaddd ymm0, ymm0, ymmword ptr [rdi + rax*4]
    vmovdqu ymmword ptr [rdi + rax*4], ymm0

```
</details>

## 4. `_Atomic`
- This was introduced in C11.
- `<stdatomic.h>` header file is required
- Used many in concurrent programming
- **Provides load/store and read-modify-write** operations.
- ***The entire increment operation is treated as one indivisible step.***

**Illustration**  
Without `_Atomic`
```mathematica
Thread A: Read counter = 5
Thread B: Read counter = 5
Thread A: Add 1 → 6
Thread B: Add 1 → 6
Thread A: Write 6 back
Thread B: Write 6 back  <-- lost increment, final counter = 6, expected 7
```
With `_Atomic`
```mathematica
Thread A: atomic_fetch_add increments counter from 5 to 6 atomically
Thread B: atomic_fetch_add increments counter from 6 to 7 atomically
Final counter = 7

```
- Usage of _Atomic
```c
_Atomic int counter; // simple

typedef struct { // with struct
    int x, y;
} Point;
_Atomic Point atomic_point;

_Atomic int *ptr; // with pointer

typedef _Atomic int atomic_int; // with typedef
atomic_int counter;

```
```c
#include <stdatomic.h>

_Atomic int counter = 0;
atomic_fetch_add(&counter, 1); // this is a special function from stdatomic.h
```

***Example of atmoic operation***
Take a counter, it should be counted to 200.  
But use two threads, each can only increase 100.  
No value should be skipped due to race condition.  
```c
#include <stdio.h>
#include <stdatomic.h>
#include <threads.h>

atomic_int counter = 0;  // shared atomic counter

int increment(void *arg) {
    for (int i = 0; i < 100000; i++) {
        atomic_fetch_add(&counter, 1);  // atomic increment
    }
    return 0;
}

int main() {
    thrd_t t1, t2;

    thrd_create(&t1, increment, NULL);
    thrd_create(&t2, increment, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    printf("Final counter value: %d\n", counter);
    return 0;
}

```

<hr>

**Other Atmoic function from stdatomic.h**
| Function                         | Prototype                                                                                          | Purpose                          | Description                                                                                                  |
| -------------------------------- | -------------------------------------------------------------------------------------------------- | -------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| `atomic_load`                    | `type atomic_load(const volatile atomic_type *object);`                                            | Atomic read                      | Atomically reads the value of an atomic variable.                                                            |
| `atomic_store`                   | `void atomic_store(volatile atomic_type *object, type desired);`                                   | Atomic write                     | Atomically writes a value to an atomic variable.                                                             |
| `atomic_exchange`                | `type atomic_exchange(volatile atomic_type *object, type desired);`                                | Atomic swap                      | Atomically replaces the value, returns the old value.                                                        |
| `atomic_fetch_add`               | `type atomic_fetch_add(volatile atomic_type *object, type operand);`                               | Atomic addition                  | Atomically adds operand; returns previous value.                                                             |
| `atomic_fetch_sub`               | `type atomic_fetch_sub(volatile atomic_type *object, type operand);`                               | Atomic subtraction               | Atomically subtracts operand; returns previous value.                                                        |
| `atomic_fetch_or`                | `type atomic_fetch_or(volatile atomic_type *object, type operand);`                                | Atomic bitwise OR                | Atomically performs bitwise OR with operand; returns previous value.                                         |
| `atomic_fetch_and`               | `type atomic_fetch_and(volatile atomic_type *object, type operand);`                               | Atomic bitwise AND               | Atomically performs bitwise AND with operand; returns previous value.                                        |
| `atomic_fetch_xor`               | `type atomic_fetch_xor(volatile atomic_type *object, type operand);`                               | Atomic bitwise XOR               | Atomically performs bitwise XOR with operand; returns previous value.                                        |
| `atomic_compare_exchange_strong` | `bool atomic_compare_exchange_strong(volatile atomic_type *object, type *expected, type desired);` | Atomic compare and swap (strong) | Atomically compares the object with *expected*; if equal, replaces with desired. Returns true if successful. |
| `atomic_compare_exchange_weak`   | `bool atomic_compare_exchange_weak(volatile atomic_type *object, type *expected, type desired);`   | Atomic compare and swap (weak)   | Like strong, but may fail spuriously (used in loops).                                                        |
