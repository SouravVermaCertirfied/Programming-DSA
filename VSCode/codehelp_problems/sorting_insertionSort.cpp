#include<iostream>
#include<vector>

using namespace std;
/*

*/
void insertionSort(vector<int> &input);
void printVector(vector<int> &input);

int main(){
    vector<int> input{90,2,14,58,43,567,785,45,6};
    cout<<"Size of the array : "<<input.size()<<endl;
    insertionSort(input);
    return 0;
}

void insertionSort(vector<int> &input){
    int pass = 0;
    for(int i=0;i<input.size()-1;i++){
        pass++;
        for(int j=i+1;j<input.size();j++){
            if(input[i]>input[j]) {
                swap(input[i],input[j]);
            }
        }
        cout<<"Pass : "<<pass<<" the array is --> ";
        printVector(input);
    }
}

void printVector(vector<int> &input){
    for(int i=0;i<input.size();i++){
        cout<<input[i]<<" ";
    }
    cout<<endl;
}