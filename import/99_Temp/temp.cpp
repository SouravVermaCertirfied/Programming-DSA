#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int countPairs(vector<int> &arr, int target) {
    // Complete the function
    int count = 0;
    int left = 0, right = arr.size()-1;
    int sum;
    while(left<right){
        sum = arr[left] + arr[right];
        if(sum > target)
            right--;
        else if(sum < target)
            left++;
        else{
            int l = arr[left];
            int r = arr[right];
            
            int lcount = 0;
            int rcount = 0;
            
            while(left < right && (arr[left]==l) && (arr[right]==r)){
                lcount += 1;
                rcount += 1;
                left++;
                right--;
            }
            count += (lcount * rcount);
            if(!(left < right ))
                return count;

            int llcount = 0;
            int rrcount = 0;
            
            while(left<right && arr[left]==l){
                llcount++;
                left++;
            }
            while(left<right && arr[right]==r){
                rrcount++;
                right--;
            }
            count += ( (llcount*rcount) + (lcount*rrcount));
        }
    }
    return count;
}

vector<int> sumClosest(vector<int>& arr, int target) {
    // code here
    /*
    - sort the array
    - left and right
    - cal the diff, diff = target - sum(a,b)
        - if diff is zero
            - append left and right and return
            
        - else non zero diff
            - if array is empty, just append left and right to ans
            - if array is non-empty
                - find the last difference
                    - if curr diff >= last diff, do nothing
                    - else 
                        - update ans with this left right
                        - if sum > target
                            - right--
                        - else
                            - left++
    */
    sort(arr.begin(), arr.end());
    int left = 0;
    int right = arr.size() - 1;
    vector<int> ans;
    while(left < right){
        int diff = target - (arr[left] + arr[right]);
        if(diff == 0){
            if(ans.empty()){
                ans.push_back(arr[left]);
                ans.push_back(arr[right]);
            }
            else{
                ans[0] = (arr[left]);
                ans[1] = (arr[right]);
            }
            return ans;
        }
        else{
            if(ans.empty()){
                ans.push_back(arr[left]);
                ans.push_back(arr[right]);
            }
            else{
                int lastdiff = target - (ans[0] + ans[1]);
                if(abs(diff) >= abs(lastdiff)){
                    /*do nothing*/
                }
                else{
                    ans[0] = arr[left];
                    ans[1] = arr[right];
                }
            }
            if(diff > 0)
                left++;
            else
                right--;
        }
    }
    return ans;
}

int main(){
    vector<int> arr = { 5, 2, 7, 1, 4};
    vector<int> brr = { 1, 1, 1, 1 };
    // vector<int> ans  = sumClosest(arr, 10);
    cout<<countPairs(brr, 2);
    return 0;
}
