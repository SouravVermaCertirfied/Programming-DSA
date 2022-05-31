// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

int strstr(string ,string);

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string a;
        string b;
        
        cin>>a;
        cin>>b;
        
        cout<<strstr(a,b)<<endl;
    }
}
// } Driver Code Ends


//Function to locate the occurrence of the string x in the string s.
int strstr(string s, string x)
{
     //Your code here
     if(s.length()<x.length()){
         return -1;
     }
     bool found = false;
     int len = s.length() - x.length() + 1;
     for(int i=0;i<len;i++ ){
         found = true;
         for(int j =0;j<x.length();j++){
             if(x[j] != s[i+j]){
                 found = false;
             }
         }
         if(found){
             return i;
         }
     }
     return -1;
}