#include <iostream>

using namespace std;


/* Problem: Program to find whether a given number is power of 2
   Approch: Expected : If there is only 1 bit as 1 in the number eg 1000
            then (N-1) will have all                                0111
            if both are AND then it will become zero.
            then we know that this was a power of 2.
   TC : O(1)
   SC : O(1)
*/
/* below solution also has a variat like return (n > 0) && ((n & (~(n-1))) == n); using AND and NOT*/
bool isPowerofTwo(int n){
    if(n==0) 
        return false;
    int mask = n-1;
    if((n & mask) == 0) 
        return true;
    return false;
}

/* Problem: Program to find whether a given number is power of 2
   Approch: NAIVE : Bit shift and check if there is only one 1 in the number in binary form, use bitwise AND.
   TC : O(k)
   SC : O(1)
*/
bool isPowerofTwo_Naive(int n){
    while(n){
        if(n&1){
            n = n>>1;
            if(n == 0) return true;
            else return false;
        }
        n = n>>1;
    }
    return false;
}


int main() {
    int n = 16;
    if (isPowerofTwo(n)) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}