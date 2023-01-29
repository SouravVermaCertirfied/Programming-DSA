//============================================================================
// Name        : demos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;


int main()
{	int rows = 3;
	int cols = 5;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cout<<"*";
		}
		cout<<endl;
	}

	return 0;
}
