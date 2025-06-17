# memcpy

- `string.h` is the header file for this. Yes, it is <string.h>
- memcpy copies fixed size of data from src to destination.
- memcpy does a **shallow copy**

```c
// syntax
void *memcpy(void *dest, const void *src, size_t n   );
```

## Interview Questions

### 1. Implement your own memcpy
```c
void *memcpy(char *dest, const char *src, int size){
    
    // must type-cast to unsigned char for byte-wise copying
    unsigned char *ptr = (unsigned char*) dest;
    const unsigned char *s = (const unsigned char*) src;
    for(int i=0;i<size;i++){
        ptr[i] = s[i];
    }
    return dest;
}
```
### 2. code to illustrate shallow copy of memcpy
```c
struct Person{
    char *name;
};

int main(){
    struct Person p1;
    char *myname = "verma";
    p1.name = myname;

    struct Person p2;
    memcpy(&p2, &p1, sizeof(p1));
    // After memcpy both p2.name and p1.name are \
    // pointing to the same memory address - SHALLOW COPY
    
}
```
### 3. Implmement your own memcpy function that does deep copy.  
- By default memcpy does shallow copy.
- Changes need to be made to make it deep copy.
- Below is the same code for it  
    **Level 3.1** Simple deep copy for a Struct having a pointer.
    ```c
    struct Person{
        char *name;
    };

    struct Person *custom_deepCpy_memcpy(struct Person *dest, struct Person *src){
        
    }
    ```
    ```c
    int main(){
        struct Person p1, p2;
        p1.name = "verma";
        
    }
    ```

### 4. Use `memcpy` to colne a 2D matrix
- a. Create function to clone a matrix
```c
// input is src, rows and cols
// notice memory is being allocated in heap so that it can be returned
int **cloneMatrix_memcpy(int **src, int rows, int cols){
    int **dest = malloc(rows * sizeof(int *)); 
    for(int i=0; i<rows; i++){
        dest[i] = malloc(cols * sizeof(int *));
        memcpy(dest[i], src[i], cols * sizeof(int *));
    }
    return dest;
}
```
- b.1 Create a function to free the allocated matrix (probing question)
```c
void free_matrix(int **src, int rows){
    if(src == NULL) return;
    for(int i=0; i<rows; i++){
        free(src[i]); // free each row
        src[i] = NULL; // OPTIONAL enhancement to ensure there is no dangling pointer
    }
    free(src); // free the array of pointers
    src = NULL; // OPTIONAL
}

```
calling for b.1
```c
int **clone = cloneMatrix_memcpy(src, rows, cols);
free_matrix(clone, rows);
```
- b.2 Improve b.1 to make sure that the calling pointer is also nullified
    Notice usage of triple stars in `src` <span style="color:red;"><strong>***</strong></span>
```c
void free_matrix(int ***src, int rows) {
    if (src == NULL || *src == NULL) return;

    for (int i = 0; i < rows; i++) {
        free((*src)[i]);
        (*src)[i] = NULL;
    }

    free(*src);
    *src = NULL;  // Now this actually nullifies the caller’s pointer
}
```
calling function
```c
int **matrix = allocate_matrix(...);
free_matrix(&matrix, rows);

```


