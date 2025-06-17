#include <stdio.h>

/* Problem: Given an array of positive integers. All numbers occur an even number of times 
            except one number which occurs an odd number of times. 
            Find the number in O(n) time & constant space.
   Approch: The Best Solution is to do bitwise XOR of all the elements. 
            XOR of all elements gives us odd occurring elements. 
   TC : O(n)
   SC : O(1) 
*/

   int getOddOccurrence(int *arr, int n){
    int ans = 0;
    for(int i=0; i<n; i++){
        ans = ans ^ arr[i];
    }
    return ans;
   }

int main() {
    int ar[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    int n = sizeof(ar)/sizeof(ar[0]);
    
    // Function calling
    printf("%d", getOddOccurrence(ar, n));
    
    return 0;
}