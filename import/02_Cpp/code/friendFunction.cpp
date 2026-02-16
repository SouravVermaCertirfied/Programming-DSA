#include<iostream>
using namespace std;

class A{
    private:
        int id;
    public:
        void function();    
};

class B{
    public:
        void printId(A &a){
            cout<<a.id;
        }
};

int main(){
    return 0;
    
}