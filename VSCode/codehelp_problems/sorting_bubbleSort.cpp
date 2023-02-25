#include<iostream>
#include<vector>

using namespace std;
/*
 1. Repeatedly swapping the adjacent elements if they are in the wrong order
 2. Largest element will find its place first
*/
void bubbleSort(vector<int> &input);
void bubbleSortWithSwapCheck(vector<int> &input); /*worst condition will happen when it is reverse sorted*/
void printVector(vector<int> &input);

int main(){
    vector<int> input{90,2,14,58,43,567,785,45,6};
    cout<<"Size of the array : "<<input.size()<<endl;
    cout<<endl<<"Bubble sorting now:";
    bubbleSort(input);
    cout<<endl<<"bubbleSortWithSwapCheck sorting now:";
    bubbleSortWithSwapCheck(input);
    return 0;
}

void bubbleSort(vector<int> &input){
    int pass = 0;
    for( int i=0;i<input.size();i++){
        pass++;
        for(int j=0;j<input.size()-i-1;j++){
            if(input[j]>input[j+1]){
                swap(input[j], input[j+1]);
            }
        }
        cout<<"Pass : "<<pass<<" ";
        printVector(input);
    }
}

void bubbleSortWithSwapCheck(vector<int> &input){
    int pass = 0;
    bool swapOccured = false;
    for( int i=0;i<input.size();i++){
        pass++;
        swapOccured = false;
        for(int j=0;j<input.size()-i-1;j++){
            if(input[j]>input[j+1]){
                swap(input[j], input[j+1]);
                swapOccured = true; /*extra check added to stop sorting if array is sorted by now*/
            }
        }
        cout<<"Pass : "<<pass<<" ";
        printVector(input);

        if(!swapOccured){
            break;
        }
    }
}

void printVector(vector<int> &input){
    for(int i=0;i<input.size();i++){
        cout<<input[i]<<" ";
    }
    cout<<endl;
}