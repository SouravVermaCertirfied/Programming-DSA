//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    // Function is to check whether two strings are anagram of each other or not.
    bool areAnagrams(string& s1, string& s2) {
        // Your code here
        if(s1.length() != s2.length())
            return false;
        vector<double> ss1(26,0), ss2(26,0);
        const int A = 97;
        for(int i=0;i<s1.length();i++){
            ss1[(int)s1[i] - A] +=1;
            ss2[(int)s2[i] - A] +=1;
        }
        for(int i=0;i<26;i++){
            if(ss1[i] != ss2[i])
                return false;
        }
        return true;
    }
};

//{ Driver Code Starts.

int main() {

    int t;

    cin >> t;

    while (t--) {
        string c, d;

        cin >> c >> d;
        Solution obj;
        if (obj.areAnagrams(c, d))
            cout << "true" << endl;
        else
            cout << "false" << endl;
        cout << "~" << endl;
    }
}

// } Driver Code Ends