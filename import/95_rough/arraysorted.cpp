#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

class Solution {
public:
    string prep(int i, int j){
        return (to_string(i) + "->" + to_string(j));
    }
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ans;
        if(nums.size()==0) return ans;

        int l = 0;
        int r = 0;
        int m = nums.size();
        for(int i=0; i<m ; i++){
            
        }
        return ans;
    }
    
};

int main(){
    vector<int> nums;
    Solution s;
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(7);
    int target = 9;
    vector<string> ans = s.summaryRanges(nums);
    for(auto x : ans) cout<<x<<endl;
    cin.get();
    return 0;
}