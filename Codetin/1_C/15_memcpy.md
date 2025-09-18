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

However, we can approximate a generic solution using function pointers and void pointers, where:  
- You write a generic wrapper function that performs a deep copy using a user-supplied deep-copy logic.  
- You pass the custom deep-copy logic for each struct type.  
**the idea is to have a generic wrapper, that abstracts the structure specific copier function, and the calling function main tells the generic copier, which struct-specific-function has to be called for deep copy.** Here is the code now :  
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a function pointer type for deep copying
typedef void *(*deep_copy_func)(void *dest, const void *src);

// Generic deep copy using function pointer
void *generic_deep_copy(void *dest, const void *src, deep_copy_func copier) {
    if (!dest || !src || !copier) return NULL;
    return copier(dest, src);
}


struct Person {
    int rollno;
    char *name;
};

// Deep copy function specific to struct Person
void *deep_copy_person(void *dest, const void *src) {
    struct Person *d = (struct Person *)dest;
    const struct Person *s = (const struct Person *)src;

    d->rollno = s->rollno;

    if (s->name) {
        d->name = (char *)malloc(strlen(s->name) + 1);
        if (!d->name) {
            perror("Memory allocation failed");
            return NULL;
        }
        strcpy(d->name, s->name);
    } else {
        d->name = NULL;
    }

    return d;
}


int main() {
    struct Person p1, p2;
    p1.rollno = 42;
    p1.name = strdup("Verma"); // dynamic allocation to test deep copy

    generic_deep_copy(&p2, &p1, deep_copy_person);

    printf("Original: rollno = %d, name = %s\n", p1.rollno, p1.name);
    printf("Copied  : rollno = %d, name = %s\n", p2.rollno, p2.name);

    // Modify original to test deep copy
    p1.name[0] = 'X';
    p1.rollno = 100;

    printf("\nAfter modifying original:\n");
    printf("Original: rollno = %d, name = %s\n", p1.rollno, p1.name);
    printf("Copied  : rollno = %d, name = %s\n", p2.rollno, p2.name);

    // Clean up
    free(p1.name);
    free(p2.name);

    return 0;
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
## Interview qustion (this is tricky!)

Give the output of the below code snippet.  

```c
here is the code. #include <stdio.h>
#include <string.h>

struct car{
  int vin;
  char *name;
};

int main()
{
    printf("Hello World");
    char *myname = (char*)"verma";
    struct car c1 = {.vin = 10 , .name = myname };
    struct car c2;
    memcpy(&c2, &c1, sizeof(c1));
    printf("%s", c2.name);
    myname = (char*)"sharma";
    printf("%s", c2.name);
    return 0;
}
```

🔍 Why this output ?  
```
printf("Hello World");
→ Prints: Hello World

myname = `verma";
→ myname points to string `verma`

struct car c1 = {...}
→ c1.name points to `verma`

memcpy(&c2, &c1, sizeof(c1));
→ Copies content of c1 to c2, including the pointer, not the string itself. So c2.name also points to `verma".

printf("%s", c2.name);
→ Prints: verma

myname = `sharma";
→ Changes myname, but doesn't affect c2.name or c1.name — they still point to `verma`

printf("%s", c2.name);
→ Again prints: verma
```


