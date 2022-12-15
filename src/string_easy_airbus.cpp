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

/*
 * Input  : This is a sample text
 * Output : This13 is11 a10 sample4 text0
 *
 * */

int main()
{
	char input[] = "This is a sample text";
	int values[10] = {};
	int vp=-1;
	values[++vp] = 0;
	int N = sizeof(input)-1;
	int ip=N-1;
	int count = 0;
	while(ip>=0){
		if(input[ip]!=' '){
			count++;
		}
		else{
			values[++vp] = count;
		}
		ip--;
	}
	ip=0;
	while(ip<=N-1){
		if(input[ip]==' '){
			cout<<values[vp--];
		}
		cout<<input[ip];
		ip++;
	}
	cout<<0;
	return 0;
}
