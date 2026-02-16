# Arrays;

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