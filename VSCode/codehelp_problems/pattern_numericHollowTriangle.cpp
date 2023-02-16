//============================================================================
// Name        : demos.cpp
// Author      : Sourav Kumar Verma
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
Print the pattern:
1
1 2
1   3
1     4
1 2 3 4 5    
*/

#include <iostream>
#include <string>
using namespace std;

void printPattern(int size){
    for(int i=1;i<=size;i++){
        for(int j=1;j<=i;j++){
            if(j==1 || j==i || i==size)
                cout<<j<<"\t";
            else
                cout<<"\t";

        }
        cout<<endl;
    }
}

int main()
{	int size = 9;
    printPattern(size);
    return 0;
}
