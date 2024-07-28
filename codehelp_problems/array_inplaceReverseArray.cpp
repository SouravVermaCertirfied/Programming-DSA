//============================================================================
// Name        : demos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

/**
 * if the array is 1,2,3,4,5
 * then print 1 5 2 4 3
 *  	#####
 * 		#   #
 *  	#####
 */
void printExtreme(int arr[], int size){
	int left = 0;
	int right = size-1;
	while(left<=right){
		if(left<right){
			cout<<arr[left]<<" "<<arr[right]<<endl;
		}
		else{
			cout<<arr[left]<<endl;
		}
		left++;
		right--;
	}
}

void inplaceReverseArray(int arr[], int size){
	int left = 0;
	int right = size-1;
	int temp = 0;
	while(left<=right){
		if(left<right){
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
		left++;
		right--;
	}
}

void printArr(int arr[], int size){
	cout<<"Now priting the arrary"<<endl;
	for(int i=0;i<size;i++){
		cout<<arr[i]<<" ";
	}
}
int main()
{
	int size = 15;
	int size1 = 1;
	int arr1[] = {1};
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	printExtreme(arr, size);
	cout<<"this is next loop"<<endl;
	printExtreme(arr1, size1);
	cout<<"Now running inplaceReverseArray"<<endl;
	inplaceReverseArray(arr, size);
	cout<<"Now running printArr"<<endl;
	printArr(arr, size);
	return 0;
}
