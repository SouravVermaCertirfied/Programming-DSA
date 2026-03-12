/* deisgn a circular queue,
that overwrites the oldest item if full*/
#include<iostream>
using namespace std;

#define CAP 10u

int arr[CAP];
int front = -1;
int rear = -1;
int qsize = 0;
int cap = CAP;

void insert(int val){
    if(qsize == 0 ){ // first element
        qsize++;
        front++; rear++;
        arr[rear] = val;
        return;
    }
    if(((rear+1)%cap) == front){
        front = ( front + 1 ) % cap;
        rear  = ( rear + 1 ) % cap;
        arr[rear] = val;
        return;
    }
    else{
        rear  = ( rear + 1 ) % cap;
        arr[rear] = val;
        qsize++;
        return;
    }

}

void del(){
    if(qsize==0){
        cout<<"Underflow"<<endl; return;
    }
    if(qsize==1){
        front = -1;
        rear = -1;
        qsize = 0;
        return;
    }
    front = (front + 1 ) % cap;
    qsize--;
    return;
}

void printall(){
    if(qsize == 0){
        cout<<"Underflow"<<endl;
        return;
    }
    int k = qsize;
    int i = front;
    while(k){
        cout<<arr[i]<<" ";
        i = (i + 1) % cap;
        k--;
    }
    cout<<endl;
    return;
}

int main(){
    for(int i=0 ; i<15; i++){
        insert(i);
        printall();
    }
    for(int i=0; i<15; i++){
        del();
        printall();
    }
    cin.get();
    return 0;
}
