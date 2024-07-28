#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void sortColor(vector<int> &nums);
void printVector(vector<int> nums);
void bubbleSortApproch(vector<int> &nums);
void countingMethodApproch(vector<int> &nums);
void threePointerApproch(vector<int> &nums);



int main(){
    vector<int> nums{2,0,2,1,1,0};
    printVector(nums);
    sortColor(nums);
    printVector(nums);
    return 0;
}


void sortColor(vector<int> &nums){
    countingMethod(nums);
    
}

void threePointerApproch(vector<int> &nums){
    
}

void countingMethod(vector<int> &nums){ /*time complexity is O(1), but this cannot be used as this not in-place sorting*/
    vector<int> v{0,0,0};

    /*count each of the item how many times they are occuring*/
    for(int i=0;i<nums.size();i++){
        v[nums[i]] = v[nums[i]] + 1;
    }

    /*fill the oringal array with the number of times they have occured*/
    int index = 0;
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i];j++){
            nums[index] = i;
            index++;
        }
    }
}

void bubbleSort(vector<int> &nums){
    int temp = 0;
    for(int i=0;i<nums.size();i++){
        for(int j=i+1;j<nums.size();j++){
            if(nums[i]>nums[j]){
                swap(nums[i], nums[j]);
            }
        }
    }
}

void printVector(vector<int> nums){
    for( int item : nums){
        cout<<item<<" ";
    }
    cout<<endl;
}