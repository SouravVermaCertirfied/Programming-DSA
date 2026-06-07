#include<iostream>
using namespace std;

class B;

class A{
    int id = 10;
    public:
        A(int id) : id(id);
        friend void B :: printme(A a);
};

class B{
    public:
        void printme(A a){
        cout<<a.id;
    }
};


int main(){
    A a(10);
    return 0;
}