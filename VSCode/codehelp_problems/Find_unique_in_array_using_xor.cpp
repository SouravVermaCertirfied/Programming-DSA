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
*WAP find unique element if every other element occurs twice
*
*/



int findUnique(vector<int> arr){
	int ans = 0;
	for(unsigned int i =0;i<arr.size();i++){
		ans = ans ^ arr[i];
	}
	return ans;
}

int main()
{
	vector<int> arr{1,2,3,1,2,3,4};
	cout<<"The output is:"<<findUnique(arr);
	return 0;
}
