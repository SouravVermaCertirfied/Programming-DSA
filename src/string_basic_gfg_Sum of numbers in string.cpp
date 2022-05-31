// { Driver Code Starts
// C++ program to calculate sum of all numbers present
// in a string containing alphanumeric characters
#include <iostream>
using namespace std;


 // } Driver Code Ends


class Solution
{
    public:
    //Function to calculate sum of all numbers present in a string.
    int findSum(string str)
    {
    	
    	// Your code here
    	string temp = "";
    	int number = 0;
    	int sum = 0;
    	for(int i=0; i<str.length();i++){
    	    if(str[i]>=48 && str[i]<=57){
    	        number = (number * 10) +  (str[i] - 48);
    	    }
    	    else{
    	        sum += number;
    	        number = 0;
    	    }
    	}
    	sum +=number;
    	return sum;
    	
    }
};

// { Driver Code Starts.

// Driver code
int main()
{
	// input alphanumeric string
	int t;
	cin>>t;
	while(t--)
	{
	    string str;
	    cin>>str;
	    Solution obj;
	    cout << obj.findSum(str);
        cout<<endl;
	}
	return 0;
}
  // } Driver Code Ends