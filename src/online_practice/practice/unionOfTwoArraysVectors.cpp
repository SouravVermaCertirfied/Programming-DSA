//============================================================================
// Name        : demos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

/**
*WAP union of two arrays,
*
*/

vector<int> unionOfTwoArrays(vector<int> arrA, vector<int> arrB){
	vector<int> ans;
	for(unsigned int i =0;i<arrA.size();i++){
		ans.push_back(arrA[i]);
	}
	for(unsigned int j =0;j<arrB.size();j++){
		ans.push_back(arrB[j]);
		}
	return ans;
}

void printVector(vector<int> arr){
	for(unsigned int i=0;i<arr.size();i++){
		cout<<arr[i]<<" ";
	}
}
int main()
{
	vector<int> arr;
	vector<int> arrA{1,2,3,4,5};
	vector<int> arrB{6,7,8,9,10};
	arr = unionOfTwoArrays(arrA, arrB);
	printVector(arr);
}
