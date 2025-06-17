# Malloc and Calloc

- Declared in hearder `stdlib.h`.  
- Allocates memory to the **heap**.      
- `calloc` Intializes all the bytes to zero. Zero init makes it relatively slower.
- `malloc` does not intialize the values, hence may contain garbage values.
- Both return `NULL` if memory allocation fails. Essential to check for NULL before usage.

Notice in the below syntax that the <strong style="color:red;">return type is a void</strong>.    
Hence, it must be typecasted to the desired data type pointer.


## `malloc()`
It takes input of just only **one parameter**.  

```c
// sytnax
void malloc(int size);

// usage
int *arr = (int*)malloc(40); // this allocates memory of 10 bytes to arr.
char *arr = (char*)malloc(10); // 
```
**Questions**
- Where is the memory allocated ? Heap.
- Implement your own malloc.

## `calloc()`

The only differnce in `calloc` is that 
```c
// syntax
void* calloc(int N, int size); // Allocated size if N * size.

// usage
int *arr - (int *)calloc(10,4); // allocates 10*4 = 40 bytes
int *arr = (int*)calloc(10, sizeof(int)); // same result as above, considering int is 4 bytes
```

- Implement your own calloc