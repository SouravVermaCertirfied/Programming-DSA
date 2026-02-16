#include<iostream>
using namespace std;

struct Node{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int k){
        data = k;
        left = NULL;
        right = NULL;
    }
};

//left root right
void inorder(Node *root){
    if(root == NULL)
        return;
    
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
    return ;
}

//root left right
void preorder(Node *root){
    if(root == NULL){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root){
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}


        10
        
    20      30
    
        40      50
int main(){
    Node *root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->right->left = new Node(40);
    root->right->right = new Node(50);

    inorder(root);
    cout<<endl;
    preorder(root);
    cout<<endl;
    postorder(root);

    return 0;
}