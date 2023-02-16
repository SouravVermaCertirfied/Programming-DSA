#include<iostream>

using namespace std;


/*
print the pattern:

1 2 3 4 5
1     4
1   3
1 2
1

*/

void printNumericInvertedHollowTriangle(int size){
    
    for(int i=1;i<=size;i++){
        for(int j=1;j<=((size+1)-i);j++){
            if(j==1 || j==((size+1)-i) || i==1){
                cout<<j<<"\t";
            }
            else{
                cout<<"\t";
            }
        }
        cout<<endl;
    }

}

int main(){
    int size = 5;
    printNumericInvertedHollowTriangle(size);
    return 0;
}