# `break`

Break only breaks one loop in the nested loops,  
it does not break all the loops.

**example:**
```c
#include <stdio.h>

int main()
{
    printf("Hello World\n");
    int count = 0;
    for(int i=10; i<15; i++){
        printf("%d ", i);
        for(int j=100; j<105; j++){
            printf("%d ", j);
            if(j==103)
                break;
        }
        printf("\n");
    }
    

    return 0;
}
```
**output**
```
Hello World
10 100 101 102 103
11 100 101 102 103
12 100 101 102 103
13 100 101 102 103
14 100 101 102 103
```