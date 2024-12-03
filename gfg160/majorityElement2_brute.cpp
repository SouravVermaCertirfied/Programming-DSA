/*
You are given an array of integer arr[] where each number represents a vote to a candidate. Return the candidates that have votes greater than one-third of the total votes, If there's not a majority vote, return an empty array. 

Note: The answer should be returned in an increasing format.

Examples:

Input: arr[] = [2, 1, 5, 5, 5, 5, 6, 6, 6, 6, 6]
Output: [5, 6]
Explanation: 5 and 6 occur more n/3 times.

Input: arr[] = [1, 2, 3, 4, 5]
Output: []
Explanation: no candidate occur more than n/3 times.

 */
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    // Function to find the majority elements in the array
    int isPresent(int k, vector<int> &nums){
        for(int i=0;i<nums.size();i++){
            if(nums[i] == k)
                return i;
        }
        return -1;
    }
    vector<int> findMajority(vector<int>& arr) {
        // Your code goes here.
        int onethird = arr.size() / 3;
        vector<int> ans;
        vector<int> nums;
        vector<int> counts;
        int pos;
        for( int i=0; i<arr.size() ; i++){
            pos = isPresent(arr[i], nums);
            if(pos > (-1)){
                counts[pos] = counts[pos] + 1;
            }
            else{
                nums.push_back(arr[i]);
                counts.push_back(1);
            }
        }
        
        for(int i=0;i<nums.size();i++){
            if(counts[i]>onethird){
                ans.push_back(nums[i]);
            }
        }
        stable_sort(ans.begin(), ans.end());
        return ans;
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {

        string s;
        getline(cin, s);
        stringstream ss(s);
        vector<int> nums;
        int num;
        while (ss >> num) {
            nums.push_back(num);
        }
        Solution ob;
        vector<int> ans = ob.findMajority(nums);
        if (ans.empty()) {
            cout << "[]";
        } else {
            for (auto &i : ans)
                cout << i << " ";
        }
        cout << "\n";
    }
    return 0;
}
// } Driver Code Ends