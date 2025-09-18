# Tree

```text
      1
    /   \
    2    3
  /   \
 4     5
```

## Tree Traversal - using recursion
1. In-order = left-root-right
2. Pre-order = root-left-right
3. Post-Order = left-right-root



```cpp
void inOrder(Node *head){
    if(head==NULL)
        return;
    inOrder(head->left);
    cout<<head->val;
    inOrder(head->right);
}
```
```cpp
void preOrder(Node *head){
    if(head==NULL)
        return;
    cout<<head->val;
    preOrder(head->left);
    preOrder(head->right);
}
```
```cpp
void postOrder(Node *head){
    if(head==NULL)
        return;
    postOrder(head->left);
    postOrder(head->right);
    cout<<head->val;
}
```
<details>
<summary>Driver code</summary>

```cpp
#include<iostream>
using namespace std;
```
```cpp
class Node{
    public:

    int val;
    Node *left = NULL;
    Node *right = NULL;

    Node(int val){
        this->val = val;
    }
};
```

```cpp
int main(){
    Node *head =  new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);
    head->left->left = new Node(4);
    head->left->right = new Node(5);

    inOrder(head); cout<<endl;
    preOrder(head); cout<<endl;
    postOrder(head); cout<<endl;
    
    return 0;
}
```
</details>