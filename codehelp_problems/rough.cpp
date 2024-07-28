#include<iostream>
#include<string>
#include<stack>

using namespace std;


class Solution {
public:

    bool isAlphabet(char ch){
        bool ans = false;
        if( ((int)ch >= 'a' && (int)ch<='z') || \
            ((int)ch >= 'A' && (int)ch<='Z')){
                ans = true;
          }
        
        return ans;
    }

    
    string reverseOnlyLetters(string s) {
        string ans;
        stack<char> stk;
        for(int i=0;i<s.length();i++){
            if(isAlphabet(s[i])){
                stk.push(s[i]);
            }
            else{
                while(!stk.empty()){
                    ans.push_back(stk.top());
                    stk.pop();
                }
                ans.push_back(s[i]);
            }
        }
        while(!stk.empty()){
            ans.push_back(stk.top());
            stk.pop();
        }

        return ans;
        
    }
};

int main(){
    
    Solution s;
    string str1 = "Test1ng-Leet=code-Q!";
    cout<<s.reverseOnlyLetters(str1);

    return 0;
}