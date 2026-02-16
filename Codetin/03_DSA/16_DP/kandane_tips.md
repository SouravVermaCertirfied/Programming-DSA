# DP DSA Tips

## 1. Kandane's Algo

Kadane’s algorithm is based on a simple idea:  
> when looking for the maximum-sum contiguous subarray, you never want to keep a prefix that reduces the sum of any future subarray.

The approach continuously evaluates whether it is better to:  
- **extend the current subarray by including the next element, or**
- **start a new subarray from the current element.**


### Maximum Subarray
Given an integer array nums, find the subarray with the largest sum, and return its sum.

<details><summary>Code Here</summary>

```cpp
    int maxSubArray(vector<int>& nums) {
        int msum = INT_MIN;
        int sum =  0;
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];
            msum = max(sum, msum);
            if(sum < 0) sum = 0;
        }
        return msum;
    }
```
</details>

### Maxisum Subarray Variations
- find the length of the maximum subarray - find the range index - find range when multiple indexes exist.

```c
/*range*/
vector<int> fun(vector<int> &arr){
    int sum = 0;
    int msum = INT_MIN;
    vector<int> ans;
    int left = 0
    int right = 0;
    for(int i=0; i<arr.size(); i++){
        sum += arr[i];
        right = i;
        msum = max(msum, sum);
        if(sum < 0){
            sum = 0;
            left = i+1;
        }
    }
    return ans;
}

```