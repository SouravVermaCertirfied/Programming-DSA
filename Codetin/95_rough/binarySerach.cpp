#include<iostream>
#include<vector>
using namespace std;

int bSearch(vector<int> &arr, int k){

    int l = 0;
    int r  = arr.size() - 1;
    int mid;

    while(l <= r ){
        mid = l + ( r - l)/2;
        if(arr[mid] == k){
            if(mid == 0 || arr[mid -1] != k)
                return mid;
            else
                r = mid -1;
        }
        else if(k > arr[mid]){
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }

    return  -1;
}

int main(){
    vector<int> arr = {1, 2, 3, 4,4,4,4,4,4,4,4,4,4,4,4,4, 5, 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5, 6};
    int k = 5;
    cout<<bSearch(arr, k);
    return 0;
}