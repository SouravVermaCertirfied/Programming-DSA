#include<iostream>
#include<vector>

using namespace std;


int factorial(int num){
    int ans = 1;
    for(int i=1;i<=num;i++)
        ans *=i;

    return ans;
}

int main(){
    vector<int> number{1,0,4,7,101,100,105,26};
    for(int item : number){
        cout<<"Factoral for "<<item<<" is "<<factorial(item)<<endl;
    }
    return 0;
}