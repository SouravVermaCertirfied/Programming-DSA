# Height of Binary Tree

```cpp

    int maxDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        
        return 1+max(maxDepth(root->right), maxDepth(root->left));
    }


```

# Print Node at k - distance

```cpp

int printAtKDistance(Node *root, int k){
    if(root == NULL)
        return 0;

    int leftDepth = 1+printAtKDistance(root->left, k);
    if(leftDepth==k)
        cout<<root->val;
    int rightDepth = 1+printAtKDistance(root->right, k);
    if(rightDept==k)
        cout<<root->val;
        
}
```