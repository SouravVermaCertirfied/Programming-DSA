# String related functions (popular)
- `string.h` is the library that supports these two functions.

## strcmp

- `strcmp` compares the the strings. It works like `str1[i] - str2[i]`.  
- Example : ASCII of 'p' = 112, 'r' = 114. So, 112 - 114 = -2
- This property can be used to find who is lexicographically greater string.
```c
// syntax
int strcmp(const char *str1, const char *str2);

// WAP: Implement your own strcmp - Interview question

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2; // Note: Here unsigned char has been used
}

```

## strcpy

-  `strcpy` copies from souce to destination.
- Returns pointer to the destination.
- <span style = "color:red;"> Does not check the destination buffer size
this can lead to buffer overflow. User should check will implementation.</span>
```c
//syntax
char *strcpy(char *dest, const char *source);

// WAP: Implement your own strcpy - interview question

char *my_strcpy(char *dest, const char *source) {
    char *ptr = dest; // Save the original destination address
    while (*source != '\0') {
        *ptr = *source;
        source++;
        ptr++;
    }
    *ptr = '\0'; // Null-terminate the destination string
    return dest; // Return the beginning of the destination
}

```


## Questions

- Q. Implement custom memcpy that does deep copy ?

- Q. How would you implement a safer `memcpy`
    - A. It can be done by creating a wrapper function to check the conditions. Eg:
    ```c
    int mysafe_memcpy(void *dest, const void *src, int size){
        // check all the failure conditions here
        int dest_size; // implement some logic to find dest size
        if(!dest || !src || dest_size<size)
            return -1;
        memcpy(dest, src, size);
        return 0;
    }
