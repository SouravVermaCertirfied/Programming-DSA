## LC 0003 : Find the length of the longest substring without duplicate 
Given a string s, find the length of the longest substring without duplicate characters.  
Example 1:  
Input: s = "abcabcbb"  
Output: 3  
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers. 

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        int longest = 0;
        unordered_set<char> tbl;
        int left = 0, right = 0;
        
        while(right<len && left<len){
            if(tbl.find(s[right]) == tbl.end()){ // not found - incease the window
                tbl.insert(s[right]);
                longest = max(longest, (right-left+1));
                right++;
            }
            else{ // found - shift the window
                tbl.erase(s[left]);
                left++;
            }
            
        }
        return longest;
    }
};
```

## LC 1004 : Max Consecutive Ones III
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.  
Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2  
Output: 6  
Explanation: [1,1,1,0,0,1,1,1,1,1,1]  
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.  
```cpp
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, right = 0, rem = k;
        int len = nums.size();
        int ans = 0;
        while(right < len){
            if(nums[right] == 1){
                ans = max(ans, (right - left + 1));
                right++;
            }
            else{
                if(rem > 0){
                    rem--;
                    ans = max(ans, (right - left + 1));
                    right++;
                }
                else{
                    if(nums[left]==0)
                        rem++;
                    left++;
                }
                
            }
        }
        return ans;
    }
};

```