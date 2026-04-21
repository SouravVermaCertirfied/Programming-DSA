# Malloc, Calloc and Realloc

- Declared in hearder `stdlib.h` all three.  
- Allocates memory to the **heap**.      
- `calloc` Intializes all the bytes to zero. Zero init makes it relatively slower. ☢️
- `malloc` does not intialize the values, hence may contain garbage values. ☢️
- Both return `NULL` if memory allocation fails. Essential to check for NULL before usage.

Notice in the below syntax that the <strong style="color:red;">return type is a void</strong>.    
Hence, it must be typecasted to the desired data type pointer.


## 1. `malloc()`
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

## 2. `calloc()`

The only differnce in `calloc` is that 
```c
// syntax
void* calloc(int N, int size); // Allocated size if N * size.

// usage
int *arr - (int *)calloc(10,4); // allocates 10*4 = 40 bytes
int *arr = (int*)calloc(10, sizeof(int)); // same result as above, considering int is 4 bytes
```

- Implement your own calloc

## 3. `reaclloc()`
```c
void *realloc(void *ptr, size_t new_size);
```
- Changes the memory pointed by `ptr` to size `new_size`.
- Preserves the older data
    - `new_size > old_size` : old data is copied, remaining are garabge value.
    - `new_size < old_size` : old data is copied, data beyond new_size become inaccessilbe. Hence, cleared.
```c
int *ptr;
ptr = realloc(ptr, 10 * sizeof(int)); /*invalid*/

int *arr = malloc(5 * sizeof(int));
arr = realloc(arr, 10 * sizeof(int)); /*valid */

int *brr = calloc(5, sizeof(int));
brr = realloc(brr, 10 * sizeof(int)); /*valid - extra bytes have garbage*/
```

### WAP. Implement your own dynamic array
Something similar to `vector` in cpp, that grows when needed.

<details><summary>Code here</summary>

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;      // pointer to the array
    size_t size;    // current number of elements
    size_t capacity;// allocated capacity
} DynamicArray;

// Initialize the dynamic array
void initArray(DynamicArray *arr, size_t initial_capacity) {
    arr->data = malloc(initial_capacity * sizeof(int));
    if (!arr->data) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
}

// Append an element to the array
void append(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        // Double the capacity
        size_t new_capacity = arr->capacity * 2;
        int *new_data = realloc(arr->data, new_capacity * sizeof(int));
        if (!new_data) {
            printf("Memory reallocation failed!\n");
            free(arr->data);
            exit(1);
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size] = value;
    arr->size++;
}

// Free the dynamic array
void freeArray(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

// Print the dynamic array
void printArray(DynamicArray *arr) {
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

int main() {
    DynamicArray arr;
    initArray(&arr, 2); // start with capacity 2

    // Add some elements
    for (int i = 1; i <= 10; i++) {
        append(&arr, i);
    }

    printf("Dynamic Array Elements: ");
    printArray(&arr);

    freeArray(&arr);
    return 0;
}
```
</details>


### Can you `malloc` in an ISR?
No. It’s non-reentrant and can cause a Deadlock if the main thread was already in a `malloc` call.