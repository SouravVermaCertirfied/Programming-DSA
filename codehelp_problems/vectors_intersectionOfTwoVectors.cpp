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

vector<int> intersectionOfTwoArrays(vector<int> arrA, vector<int> arrB){
	vector<int> ans;
	for(unsigned int i=0;i<arrA.size();i++){
		for(unsigned int j=0;j<arrB.size();j++){
			if(arrA[i]==arrB[j]){
				ans.push_back(arrA[i]);
				arrB[j] = -1; // -1 is being marked so that this value is not used to match again
							  // assuming the input array had only positive values
			}
		}
	}
	return ans;
}

void printVector(vector<int> arr){
	for(unsigned int i=0;i<arr.size();i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;

	for(auto value: arr){
		cout<<value<<" ";
	}
	cout<<endl;
}
int main()
{
	vector<int> arr;
	vector<int> arrA{1,2,3,4,5,8,9, 9};
	vector<int> arrB{6,7,8,9,10,555,777};
	arr = intersectionOfTwoArrays(arrA, arrB);
	printVector(arr);
}
