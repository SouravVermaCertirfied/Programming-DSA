/*
Given two strings s1 and s2. Modify both the strings such that all the common characters of s1 and s2 are to be removed and the uncommon characters of s1 and s2 are to be concatenated.
Note: If all characters are removed print -1.
*/

// { Driver Code Starts
// C++ program Find concatenated string with 
// uncommon characters of given strings 
#include <bits/stdc++.h> 
using namespace std; 


 // } Driver Code Ends


class Solution
{
    public:
    //Function to remove common characters and concatenate two strings.
    string concatenatedString(string s1, string s2) 
    { 
        // Your code here
        int sc1[128] = {0};
        int sc2[128]= {0};
        int res[128]= {0};
        vector<char> ans;
        
        for(int i=0;i<s1.length();i++){
            sc1[s1[i]] = 1 ;
        }
        
        for(int i=0;i<s2.length();i++){
            sc2[s2[i]] = 1;
        }
        for(int i=0;i<128;i++){
            res[i] = sc1[i] + sc2[i];
        }
        for(int i=0;i<s1.length();i++){
            if(res[s1[i]] == 1){
                ans.push_back(s1[i]);
            }
        }
        for(int i=0;i<s2.length();i++){
            if(res[s2[i]] == 1){
                ans.push_back(s2[i]);
            }
        }
        string s(ans.begin(), ans.end());
        if(s.length()>0){
            return s;
        }
        return "-1";

        
    }

};

// { Driver Code Starts.

/* Driver program to test above function */
int main() 
{ 
	int t;
	cin >> t;
	
	while(t--){
    	string s1, s2;
    	cin >> s1 >> s2;
    	Solution obj;
    	string res = obj.concatenatedString(s1, s2);
    	cout<<res<<endl;
	}
	return 0; 
}
  // } Driver Code Ends