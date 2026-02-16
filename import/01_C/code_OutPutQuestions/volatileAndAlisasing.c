/*==========================================================
 Q1: Pointer Aliasing and volatile
==========================================================*/
/*
Question:
What is the output of this program? Why does `volatile` matter?
Expected Output: 20 30
Explanation:
- volatile ensures every access reads memory, preventing caching.
- *p1 = 20 → x = 20
- print *p2 → 20
- x = 30 → print *p1 → 30
*/
#include <stdio.h>

volatile int x1 = 10;
int main() {
    int *p1 = (int*)&x1;
    int *p2 = (int*)&x1;
    *p1 = 20;
    printf("%d ", *p2);
    x1 = 30;
    printf("%d\n", *p1);
    return 0;
}
