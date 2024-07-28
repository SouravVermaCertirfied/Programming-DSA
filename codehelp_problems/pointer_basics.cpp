#include<iostream>
using namespace std;

void fun(int *p){
    p = p + 1;

}

int main(){

    // int a = 5;
    // int *ptr = &a;
    // int *q = ptr;
    // int *s = ptr;
    // cout<<a<<endl;
    // cout<<ptr<<endl;
    // cout<<*ptr<<endl;
    // cout<<q<<endl;
    // cout<<*q<<endl;

    // int arr[5] = {1,2,3,4,5};
    // int x = 5;
    // int y = 6;
    // int *px = &x;
    // int *py = &y;
    // cout<<endl<<"Now printing"<<endl;
    // px = px+1;
    // arr = arr+1;

    int a = 5;
    int *p = &a;
    cout<<"Before a"<<a<<endl;
    cout<<"Before p"<<q<<endl;
    fun(p);
    cout<<"After a"<<a<<endl;
    cout<<"After p"<<p<<endl;
    
    return 0;
}