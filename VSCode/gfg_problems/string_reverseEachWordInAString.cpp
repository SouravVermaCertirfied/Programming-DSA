/*
Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

 

Example 1:

Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Example 2:

Input: s = "God Ding"
Output: "doG gniD"
*/


class Solution {
public:
    string reverseWords(string s) {
        
        stack<char> stk;
        string temp;
        string ans = "";
        for(int i=0;i<s.length();i++){
            if(s[i]!=' '){
                stk.push(s.at(i));
            }
            else{
                while(!stk.empty()){
                    temp = stk.top();
                    ans += (temp);
                    stk.pop();
                }
                ans.append(" ");
            }
        }
        while(!stk.empty()){
            ans += (stk.top());
            stk.pop();
        }
        return ans;
    }
};