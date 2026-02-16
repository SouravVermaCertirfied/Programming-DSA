#include <iostream>

using namespace std;

/* Problem: 
   Approch: 
   TC : O()
   SC : O()
*/
int findPostOfSetMSB(int n){
    int pos = -1;
    if(n==0)
        return pos;
    int pos = 31;
    int mask = (1<<pos);
    while(pos>=0){
        if(mask & n)
            return pos;
        else{
            mask = mask>>1;
            pos--;
        }
    }
    return -1; //control never reaches here
    
}

int setBitOnPos(int pos, int n){
    if(n == -1) return n;
    
    int mask = 1<<pos;
    return (mask | n);
}

int main() {
    int n = 100
    return 0;
}