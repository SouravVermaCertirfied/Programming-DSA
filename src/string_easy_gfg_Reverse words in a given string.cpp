/*
Given a String S, reverse the string without reversing its individual words. Words are separated by dots.

Example 1:

Input:
S = i.like.this.program.very.much
Output: much.very.program.this.like.i
Explanation: After reversing the whole
string(not individual words), the input
string becomes
much.very.program.this.like.i

*/
// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends


class Solution
{
    public:
    //Function to reverse words in a given string.
    stack<string> stk;
    string temp;
    string reverseWords(string S) 
    { 
        // code here 
        for(int i=0;i<S.length();i++){
            if(S[i]!='.'){
                temp += S.at(i);
            }
            else{
                stk.push(temp);
                temp = "";
                stk.push(".");
            }
        }
        if(!temp.empty()){
            stk.push(temp);
        }
        temp = "";
        while(!stk.empty()){
            temp += stk.top();
            stk.pop();
        }
        return temp;
    } 
};

// { Driver Code Starts.
int main() 
{
    int t;
    cin >> t;
    while (t--) 
    {
        string s;
        cin >> s;
        Solution obj;
        cout<<obj.reverseWords(s)<<endl;
    }
}  // } Driver Code Ends