#include<iostream>
#include<vector>
using namespace std;

class Node{
    public:
        int data;
        Node *next = NULL;

        Node(int data, Node *next){
            this->next = next;
            this->data = data;
        }

        Node(int data){
            this->data = data;
        }
};

Node *create(Node *head, vector<int> tbl){

}

int main(){

}
