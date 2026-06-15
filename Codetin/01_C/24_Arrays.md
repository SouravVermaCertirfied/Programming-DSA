# Arrays

## Dereferencing in matrix

### The Golden Rule of Pointer Substitution

Whenever you see the subscript notation `A[B]`, the C compiler automatically swaps it for `*(A + B)`.

If we apply this rule mechanically to `matrix[2][4]`:

1. First, treat `matrix[2]` as "A" and `4` as "B":

$$matrix[2][4] \rightarrow *(matrix[2] + 4)$$


2. Now, expand the inner `matrix[2]` using the exact same rule:

$$matrix[2] \rightarrow *(matrix + 2)$$


3. Substitute step 2 back into step 1:

$$*(*(matrix + 2) + 4)$$


If we apply this rule mechanically to `matrix[2][4]`:

1. First, treat `matrix[2]` as "A" and `4` as "B":

$$matrix[2][4] \rightarrow *(matrix[2] + 4)$$



---
**Example:**

```c

int main()
{
    int matrix[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    
    cout<<*(matrix+2)<<endl; // Prints address of start of 3rd row
    cout<<**(matrix+2)<<endl; // prints 9
    cout<<*(*(matrix+2)+2)<<endl; // prints 11

    return 0;
}
```


Below progam illustrates, what is stored in ZEROth byte when an array is defined in the below convention.

```c
#include <stdio.h>

int main()
{
    int arr[] = { 1 , 2 , 3};
    printf("%d", arr[0]);
    // output is 1
    // zeroth byte contains the left most item

    return 0;
}
```

---
<p align="left"><a href="22_Enum.md">← 22_Enum.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="25_tips2.md">25_tips2.md →</a></p>