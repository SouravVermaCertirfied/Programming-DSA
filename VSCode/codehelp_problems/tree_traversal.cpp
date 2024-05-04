//============================================================================
// Name        : demos.cpp
// Author      : Sourav Kumar Verma
// Version     : 
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class Node{
    public:
        int data;
        Node* left = NULL ;
        Node* right = NULL;
        
        Node(int val){
            this->data = val;
        }
        
};

Node* buildTree(Node* root){
    int d;
    cout<<"Enter data : ";
    cin>>d;
    cout<<endl;

    Node* node = new Node(d);

    if(d == -1){
        return NULL;
    }

    cout<<"enter data for left of : "<<d;
    root->left = buildTree(node);
    cout<<endl;
    cout<<"enter data for right of : "<<d;
    root->right = buildTree(node);
    cout<<endl;

    return node;




}

int main()
{
    cout<<"Hello world";
    Node* base = NULL;
    base = buildTree(base);


    return 0;
}