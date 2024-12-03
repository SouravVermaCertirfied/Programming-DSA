/* BRUTE FORCE SOLUTION
Problem Statement: 
    - Move all zeros to end
    - Maintain order
    - In place update of values
*/

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function template for C++
class Solution {
  public:
    void shift(int left, int right, vector<int> &arr){
        for( int i=left; i<right; i++){
            arr[i] = arr[i+1];
        }
    }
    void pushZerosToEnd(vector<int>& arr) {
        // code here
        int left    = 0;
        int right   = arr.size()-1;
        
        while(left< right){
            /* find the left most zero index*/
            while(left< right){
                if(arr[left] == 0)
                    break;
                else
                    left++;
            }
            /* find the right most non-zero index*/
            while(left< right){
                if(arr[right] != 0)
                    break;
                else
                    right--;
            }
            /* shift the values to the right, and make right to zero*/
            if(left<right){
            shift(left, right, arr);
            arr[right] = 0;
            }
        }
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        vector<int> arr;
        string input;
        getline(cin, input);
        stringstream ss(input);
        int number;
        while (ss >> number) {
            arr.push_back(number);
        }
        Solution ob;
        int n = arr.size();
        ob.pushZerosToEnd(arr);
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
// } Driver Code Ends