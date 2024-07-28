#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> number{1,0,4,7,101,100,105,26};

    for(int item : number)
    {
        (item & 1) ? cout<<item<<"\tis Odd" : cout<<item<<"\tis Even";
        cout<<endl;
    }
        
    return 0;

}