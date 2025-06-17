#include <iostream>
#include<cmath>

using namespace std;

/* Problem: Find position of the only set bit
   Approch: 
   TC : O(log(N))
   SC : O(1)
*/

int onlySetBit(int n){
    if(n==0)
        return -1;
    int mask = (n-1);
    if( mask & n ){
        return -1;
    }
    return log2(n)+1;
}

int main() {

    return 0;
}