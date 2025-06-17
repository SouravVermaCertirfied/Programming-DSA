#include<iostream>
using namespace std;

class Que{
    int q[100];
    int front = 0;
    int rear = 0;
    public:
    Que(){

    }

    bool isEmpty(){
        if(front == rear)
            return true;
        return false;
    }

    int getRear(){
        return rear;
    }

    int getFront(){
        return front;
    }

    bool insert()


};


int main(){
    
    return 0;
}