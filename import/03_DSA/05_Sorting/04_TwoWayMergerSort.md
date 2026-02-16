# Two Way Merge Sort

```cpp
#include<vector>
#include<iostream>
using namespace std; 

vector<int> twoWayMerge(vector<int> arr, vector<int> brr){
    int alen = arr.size();
    int blen = brr.size();

    int a = 0;
    int b = 0;

    vector<int> ans;

    while(a<alen && b<blen){
        ans.push_back( arr[a]<=brr[b] ? arr[a++] : brr[b++] );
    }
    while(a<alen)
        ans.push_back(arr[a++]);

    while(b<blen)
        ans.push_back(brr[b++]);

    return ans;
}

void printMe(vector<int> arr){
    
    for(int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
}

int main(){
    vector<int> arr = {1, 8, 90, 500, 550, 900};
    vector<int> brr = { 2, 6, 15, 85, 400, 800};
    printMe(twoWayMerge(arr, brr));
    return 0;
}
```

