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

---
<div style="display: flex; justify-content: space-between;">
    <a href="22_Enum.md">← 22_Enum.md</a>
    <a href="25_tips2.md">25_tips2.md →</a>
</div>