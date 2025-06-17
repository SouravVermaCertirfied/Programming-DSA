# Pointers in C

- Pointer is a variable that stores the **memory address**.
- Legal pointer operations are ` + ` , ` - ` , ` ++ ` , ` --` and comparisons `==`

| Operation        | Meaning                                         |
| ---------------- | ----------------------------------------------- |
| `p + i`, `p - i` | Move forward/back by `i` elements               |
| `p1 - p2`        | Distance **(in elements)** between `p1` and `p2`    |
| `p++`, `p--`     | Move to next/previous element                   |
| `*p`             | Dereference                                     |
| Comparisons      | `p1 == p2`, `p1 < p2`, etc. (within same array) |

## Comparisions

- Comparision operators like ` < ` , ` > ` , ` == ` , ` != ` , ` <= ` , ` => ` should be used only when being used for <span style="color:red;"><strong>pointers within a same array</strong></span> (or say a strcut, however, comparing with struct should be avoided, due to complier dependent behaviour).
- This may lead to undefined behaviour.

```c
int a[3], b[3];
int *p = &a[0];
int *q = &b[0];

if (p < q) {
    // This is undefined behavior
}
```

- Comparision with one past is OK. if `lst` is the pointer to the last element. `lst+1` can also be used for comparision.

```c
int arr[10] = {};
int *ptr = arr; // pointer to first
int *lst = ptr+10; // pointer to last + 1
```

## Dangling Pointer and Wild Pointer
- Dangling - when it had a valid address, but now it does not has a vaid address.
- Wild - when it does not has had any valid address ever.
```c
int main()
{
    int *ptr ; // WILD at this moment, as declared without any address
        {   int a = 10;
            ptr = &a ; // VALID right now as it has a valid address
        }
    *ptr = 20 ; // DANGLING pointer as 'a' has gone out of scope now
}
```

## Function Pointer
- 
```c
bool foo(int a); // declaration of foo
bool (*fptr)(int) = *foo; // Declare a function pointer to foo

int ans = fptr(42); // calling foo using a function pointer
```

## Function tables - Using Structure (Kinda- polymorphism in C)
- Let us try to understand this technique using an exmple
    - let take example of SPI and UART
    - since both are comm protolcs - they can have similar functions like INIT, READ, WRITE.
    - define functions for both and then call them.

```c
// STEP 1 : Define function poitner type
typedef void (*InitFunc)(void);
typedef uint8 (*ReadFunc)(uint8 *buff, size_t len);

// STEP 2 : Define function table struct
typedef{
    InitFunc init;
    ReadFunc read;
} DeviceOperations;

// STEP 3 : Define functions
void uart_init(void) { /*dummy*/ }
uint8 uart_read(uint8 *buff, size_t len)  { /*dummy*/ }

void spi_init(void) { /*dummy*/ }
uint8 spi_read(uint8 *buff, size_t len)  { /*dummy*/ }

// STEP 4 : Define objects for 
DeviceOperations uart_ops = {
    .init = uart_init;
    .read = uart_read;
}

DeviceOperations spi_ops = {
    .init = spi_init;
    .read = spi_read;
}

// STEP 5 : Function to use this dynamically
void use_device(DeviceOperations *device)
{
    device->init();
    uint8 buff[16];
    device->read(buff, 16);
}

// STEP 6
int main(){
    DeviceOperations *devicePtr;

    *devicePtr = &uart_ops;
    use_device(devicePtr);

    *devicePtr = &spi_ops;
    use_device(devicePtr);

}
```

## Function tables - Using Array table - aka Jump Tables
```c
#include<stdio.h>

// STEP 1 : Create a typdef for making it easy and readable
typedef void(*funDataType)(void);

// STEP 2 : Define functions
void foo(void) { printf("foo\n"); }
void boo(void) { printf("boo"); }

// STEP 3 : Put functions in table
funDataType fun_tbl[] = {
    foo,
    boo
};

// STEP 4 : Calling random - access using index
int main(){
    fun_tbl[0]();
    fun_tbl[1]();
    return 0;
}
```
**Output**
```c
foo
boo
```

## Multilevel Pointers
- A pointer can store address of another pointer.
- There is no defined limit to the number of nestings, but it can be limited due to stack-overflow limits.

```c
#include<stdio.h>

int main(){
    int a = 10;
    int *ptr = &a;
    int **dptr = &ptr;

    printf("var: %d\n", var);          
    printf("*ptr1: %d\n", *ptr1);
    printf("**ptr2: %d", **ptr2);

    return 0;
}
```

## Trick question

```c
#include <stdio.h>

int main()
{
    int a[5] = {10, 20, 30, 40, 50};   // An array of 5 integers
    int *p = (int *)(&a + 1);          // &a is the address of the entire array
                                       // &a + 1 moves the pointer by sizeof(a) bytes (i.e., 5 * sizeof(int) = 20 bytes ahead)
                                       // Casting to int* makes 'p' point just past the end of the array

    printf("%d", *(p - 1));            // p - 1 points to the last element of the array (i.e., a[4])
                                       // *(p - 1) dereferences it to get the value 50

    return 0;
}

```