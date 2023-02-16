//============================================================================
// Name        : demos.cpp
// Author      : Sourav Kumar Verma
// Version     : 
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int> v, int sum){
    vector<int> ans{0,1};
    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++)
            if(((v[i]+v[j]) == sum)){
                v.push_back(0);
                v.push_back(0);
                break;
        }
    }
    return ans;
}

int main(){
    vector<int> v{1,2,3,4,5,6,7,8,9,10};
    int sum = 7;
    vector<int> ans = twoSum(v,sum);
    cout<<"Ths pair is from: "<<ans[0]<<" and "<<ans[1];
    return 0;
}