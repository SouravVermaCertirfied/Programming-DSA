#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void printVector(vector<int> input){
    for(int item : input){
        cout<<item<<" ";
    }
    cout<<endl;
}

int simpleBinarySort(vector<int> input, int item){
   
    int steps_count = 1;
    int ans = -1;
    int left = 0;
    int right = input.size()-1;
    int mid ;

    while(left<=right){
        steps_count++;
        cout<<"Steps Count : "<<steps_count<<endl;
        mid = (left+right) / 2;
        if(input.at(mid) == item){
            ans = mid;
            break;
        }
        else if(item > input.at(mid)){
            left = mid+1;
            mid = (left+right) / 2;
        }
        else{
            right = mid-1;
            mid = (left+right) / 2;
        }
    }

    return ans;
}

int recurciveBinarySearch(vector<int> input, int item, int left, int right){
    
    if(left<=right){
        int mid =  (left+right) /2;
        if(input.at(mid) == item){
           return mid;
        }
        else if(item > input.at(mid)){
            return recurciveBinarySearch(input, item, mid+1, right);
        }
        else{
            return recurciveBinarySearch(input, item, left, mid-1);
        }
    }
    else{
        return -1;
    }
}

int main(){
    
    vector<int> input{0,1,2,3,4,5,6,7,8,9};
    printVector(input);
    int item = 9;


    int pos = simpleBinarySort(input, item); /*Simple Binary Search*/
    pos = recurciveBinarySearch(input, item, 0, input.size()-1);


    if( pos == -1){
        cout<<"Item not found";
    }
    else{
        cout<<"The item : "<<item<<" was found at position : "<<pos;
    }
    return 0;
}