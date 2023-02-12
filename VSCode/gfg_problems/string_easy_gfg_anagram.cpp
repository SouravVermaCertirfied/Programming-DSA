// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function is to check whether two strings are anagram of each other or not.
    bool isAnagram(string a, string b){
        
        // Your code here
        /*if(a.length()!=b.length()){
            return false;
        }*/
        int a1[128] = {0};
        int b1[128] = {0};
        for(int i=0;i<a.length();i++){
            a1[a[i]] += 1;
        }
        for(int i=0;i<b.length();i++){
            b1[b[i]] += 1;
        }
        
        for(int i=0;i<128;i++){
            if(a1[i] != b1[i]){
                return false;
            }
        }
        return true;
        
        
    }

};

// { Driver Code Starts.

int main() {
    
    int t;

    cin >> t;

    while(t--){
        string c, d;

        cin >> c >> d;
        Solution obj;
        if(obj.isAnagram(c, d)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

}
  // } Driver Code Ends