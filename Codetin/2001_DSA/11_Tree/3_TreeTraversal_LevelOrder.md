# Traversal - Level Order

```cpp
#include<iostream>
#include<queue>
using namespace std;

class Node{
    public:
        int val;
        Node *left = NULL;
        Node *right = NULL;
    
    Node(int val){
        this->val = val;
    }
};

void levelOrder(Node *head){
    queue<Node*> q;
    Node *temp = NULL;
    
    q.push(head);

    while(q.empty() == false){
        temp = q.front();
        cout<<temp->val;
        q.pop();

        if(temp->left != NULL)
            q.push(temp->left);

        if(temp->right != NULL){
            q.push(temp->right);
        }
    }
}


int main(){
    Node *head =  new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);
    head->left->left = new Node(4);
    head->left->right = new Node(5);
    levelOrder(head);
    return 0;
}


```