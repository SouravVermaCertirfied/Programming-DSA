#include <iostream>

using namespace std;

/* Problem: Given two numbers x and y, and a range [l, r] where 1 <= l, r <= 32. 
            The task is consider set bits of y in range [l, r] and set these bits in x also.
   Approch: 
   TC : O()
   SC : O()
*/
1111 1111 1111 1111 - 1111 1111 1111 1111 
void copySetBits(unsigned &x, unsigned y, unsigned l, unsigned r){
    int onesrequired = (l - r);
    int mask = 1<<(onesrequired)-1;
    

}

int main() {

    return 0;
}