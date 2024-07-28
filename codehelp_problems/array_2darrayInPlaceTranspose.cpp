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

void transpose2Darray(int arr[][3], int col, int row){
	int temp;
	for(int i=0; i<row; i++){
		for(int j=0+i;j<col;j++){
			temp =  arr[i][j];
			arr[i][j] = arr[j][i];
			arr[j][i] = temp;
		}
	}
}

void print2D(int arr[3][3], int col, int row){
	for(int i=0; i<row; i++){
		for(int j=0;j<col;j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	const int col = 3;
	const int row = 3;
	int arr[row][col] = {{1,2,3},{4,5,6},{7,8,9}};
	cout<<"Printing before"<<endl;
	print2D(arr,col,row);
	transpose2Darray(arr,col,row);
	cout<<"Printing after"<<endl;
	print2D(arr,col,row);
	return 0;
}
;
