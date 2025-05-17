#include<stdio.h>
#include<string.h>

/*  Given a an integer of 4 bytes
    covert it a binary number and represet it in string 
*/

/*  Brute force approch */
string getBinaryRep(int n){
    char ans[33];
    for(int i=0; i<32; i++){
        int mask = 0x01
        ans[i] = (mask & n ? '1' : '0');
    }
    ans[33] = '\0';

    return ans;
}



int main(){
    getBinaryRep(55);
    return 0;
}