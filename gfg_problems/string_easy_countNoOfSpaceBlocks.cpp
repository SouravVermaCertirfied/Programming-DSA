// { Driver Code Starts
// C++ program Find concatenated string with
// uncommon characters of given strings
#include <bits/stdc++.h>
#include<conio.h>
using namespace std;


 // } Driver Code Ends

class Solution
{
    public:
    //Function to remove common characters and concatenate two strings.
    int countSpaceBlocks(string s)
    {
        // Your code here
    	int count = 0;
    	for(int i=0;i<s.length();i++){
    		if(s[i]!=' ' && s[i+1]==' '){
    			count++;
    		}
    	}
    	if(s[0]==' ')
    		count++;
        return count;

    }

};

// { Driver Code Starts.

/* Driver program to test above function */
int main()
{
	int t;
//	cin >> t;
	t = 1;

	while(t--){
    	string s1, s2;
//    	cin >> s1 >> s2;
    	s1 = "home.    ss  ";
    	Solution obj;
    	int res = obj.countSpaceBlocks(s1);
    	cout<<res<<endl;
	}

	return 0;
}
  // } Driver Code Ends
