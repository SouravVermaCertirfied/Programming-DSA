/*==========================================================
 Q10: Static Variable in Recursion
==========================================================*/
/*
Question:
Predict the output.
Expected Output: 0 0 0
Explanation:
- static count initialized once to 3
- recursion decrements count, prints during unwinding
- static variable retains value across calls
*/
#include <stdio.h>

void func() {
    static int count = 3;
    if (--count)
        func();
    printf("%d ", count);
}

int main() {
    func();
    return 0;
}
