#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30};
    int *p = arr;

    printf("%d\n", *(p++));  // prints 10, then p points to arr[1]
    printf("%d\n", *p);      // prints 20

    return 0;
}
