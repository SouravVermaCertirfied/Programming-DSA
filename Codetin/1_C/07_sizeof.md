# `sizeof()`

- to find out the size of the variables.
- This is an opertor directly built into the lanugage.
- No header file is needed.
- There will be no symbols for this elf.
- Using `sizeof()` with array and pointers (and passing arrays and pointers).

| Expression    | Inside `main` / Declared scope                       | Inside Function Parameter      |
| ------------- | ---------------------------------------------------- | ------------------------------ |
| `sizeof(arr)` | Size of whole array (num\_elements \* element\_size) | Size of pointer (4 or 8 bytes) |
| `sizeof(ptr)` | Size of pointer                                      | Size of pointer                |

## 1. sizeof with variables
It can be used with both data types and variables.
```c
int d = 10;
int var_size = sizeof(int);
int var_size = sizeof(d);
```

## 2. sizeof with passed variable
behaviror is same

## 3. sizeof with array (local and passed scope)
```c
#include <stdint.h>

void foo(int arr[]){
    int size = sizeof(arr) // size of pointer - NOT the whole array!!
}

int main(){
    unit32_t arr[10];
    int size = sizeof(arr); // output is 4*10 = 40 bytes - size of array
}
```
## 4. sizeof with pointers (local and passed scope)
```c
int foo(int *var){
    sizeof(var); // same as pointer 32-bit or 64-bit as per the system
}
int main(){
    int *var = NULL;
    sizeof(var); // size of pointer 32-bit or 64-bit as per the system
}
```

## Find the size of a data type without using size of operator
This can be done by:  
- Creating an array of the given data type.
- Subtracting the address of 0th and 1st element, **after typecasting it to <span style="color:red;"> char * <span>**.

```c
int main(){
    int arr[2];
    int size = ((char *)&arr[1]) - ((char *)&arr[0]);
    printf("%d \n", size);
    
    char *ptr1 = (char *)&arr[0] ;
    char *ptr2 = (char *)&arr[1];
    size = ptr2 - ptr1;
    printf("%d \n", size);
    return 0;
}
```

## Find the size of a a variable without using size of operator
💡This approch can also be used for data types, buy creating a variable for that data type.
The approch is:
- create a pointer to that variable
- Increment the pointer by 1 
- Subtract the increased pointer by variable pointer to get the difference.
> _Why this approch works_ ? Because pointer arithmetic addition of 1, increase size of data type.
```c
#include <stdio.h>

int main() {
    int x;
    char *ptr1 = (char *)&x;
    char *ptr2 = (char *)(&x + 1);  // pointer to memory right after x
    int size = ptr2 - ptr1;
    printf("%d\n", size);
    return 0;
}

```

## Implement your own `sizeof` operator
It should handle both variables and data types ( native and user-defined).
- It is not possible to do this using function, as function over-loading is not supported in C.
> pssst! there can be something done using **_Generic** for C11 onwards etc, but that is too complex.
And does not even fullfill the request fully. 
- However, this can be done using macors.   
But note that parameters in the calling statement has to be handled correctly.  
This macro is capble of handling:
- variables, variable array (both user defined and native)
- arrays (both user defined and native)
- pointers also
> **Note**:  
> `&` must be used for arrays also, otherwise it will go wrong.  
> Do not just assume that `arr` is any way a address so do not need to add `&`.  
> Not adding `&` will give size of each element in the array instead of he size of whole array itself.

> While calling from the data type.  
> The expression `*(char *)0` is used as a pointer to a dummy object of type char.  
> The address 0 is just used as a placeholder

```c
#define my_sizeof(x) ((size_t)((char *)(&(x) + 1) - (char *)(&(x))))
```
Full program for example
```c
#include<stddef.h> // for size_t

#define my_sizeof(x) ((size_t)((char*)(&x+1) - (char*)(&x))) 

struct car{
    int vin;
    char name;
};

int main(){
    int a = 10;
    int arr[10];
    float f = 5.5;
    int *ptr = &a;
    struct car c1 = {1, 'a'};

    // called using variables or objects
    my_sizeof(a);
    my_sizeof(arr);
    my_sizeof(c1);
    my_sizeof(ptr);

    // called using data type itself
    my_sizeof(*(int *)0);
    my_sizeof(*(struct car *)0);
}
```
***You can also use this macro if you want to make the input for datatype easy.***
```c
#define <stddef.h>
// actual
#define my_sizeof(x) ((size_t)((char *)(&(x) + 1) - (char *)(&(x))))
// helper
#define my_sizeof_type(T) my_sizeof(*(T *)0)

//calling
int main(){
    my_sizeof_type(int);
}
```