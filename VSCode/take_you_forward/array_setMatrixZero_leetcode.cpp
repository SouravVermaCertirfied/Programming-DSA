#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void print2Dvector(vector<vector<int>> input);
void bruteSolution(vector<vector<int>> &input);


int main(){

    vector<vector<int>> input{  {1,1,1},
                                {1,0,1},
                                {1,1,1} };
    print2Dvector(input);

    bruteSolution(input);
    print2Dvector(input);

    return 0;
}

void print2Dvector(vector<vector<int>> input){

    for(int i=0;i<input.size();i++){
        for(int j=0;j<input[0].size();j++){
            cout<<input[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"*****************"<<endl;
}

void bruteSolution(vector<vector<int>> &input){
    vector<int> iv;
    vector<int> jv;

    for(int i=0;i<input.size();i++){
        for(int j=0;j<input[0].size();j++){
            if(input[i][j] == 0){
                iv.push_back(i);
                jv.push_back(j);
            }
        }
    }

    for(int i=0, k=0;i<iv.size();i++){
        k = iv[i];
        for(int j=0;j<input[0].size();j++){
            input[k][j] = 0;
        }
    }

    for(int j=0, k=0;j<jv.size();j++){
        k = jv[j];
        for(int i=0;i<input.size();i++){
            input[i][k] = 0;
        }
    }
}