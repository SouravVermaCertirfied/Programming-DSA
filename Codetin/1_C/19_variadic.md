# Variadic function `...`

- This allows unknown number of arguments to be passed to a function.
- Include `<stdarg.h>` header.
- `va_list` - to hold the variable argument list
- `va_start` - init the list
- `va_arg` - gets each argument
- `va_end` - clean up

## Example:  
Add all the passed number to variadic function.  
```c
#include<stdio.h>
#include<stdarg.h>

int sumIt(int count, ... ){
    va_list nums;
    va_start(nums, count);
    int sum = 0;
    for(int i=0; i<count; i++){
        sum += va_arg(nums, int);
    }

    va_end(nums);
    return sum;
}

int main(){
    int count = 3;
    printf("%d",sumIt(3, 1, 2, 3));
    return 0;
}
```

### Trick question:  
Implement a varidac function but do not pass the count of the arguments.  
_Answer_: For such senario we can pass the a terminating arugument, 
and the and the variadic function should handle the logic.  
eg. some like in a list of +ve integers, the end of arguments can be -ve integer,
OR an argument of differnt data type.

## Implement your own printf function

```c
#include <stdio.h>
#include <stdarg.h>

// Helper: print an integer number (handles negative)
void print_int(int num) {
    if (num < 0) {
        putchar('-');
        num = -num;
    }
    if (num / 10)
        print_int(num / 10);
    putchar((num % 10) + '0');
}

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            if (*p == '\0') break;

            switch (*p) {
                case 'd': {
                    int val = va_arg(args, int);
                    print_int(val);
                    break;
                }
                case 'c': {
                    int val = va_arg(args, int); // char promoted to int
                    putchar(val);
                    break;
                }
                case 's': {
                    char *str = va_arg(args, char *);
                    if (str == NULL) str = "(null)";
                    while (*str) {
                        putchar(*str++);
                    }
                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(*p);
                    break;
                }
            }
        } else {
            putchar(*p);
        }
    }

    va_end(args);
}

int main() {
    my_printf("Hello %s!\nNumber: %d, Char: %c, Percent: %%\n", "world", 42, 'A');
    return 0;
}

```