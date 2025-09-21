# Binary Search Tree

- For every element, keys in left side are smaller and keys in the right side are greater.
- All the keys are considered as distinct.
- It is a linked, data strcture.
- Represented same as binary-trees.

- all the operations on the BST are depenedent on height, so if the height is not balanced (ie right and left have almost same number of items)

## Opertaions
- serach
- keep inserting.

<details><summary>Code for Node Structure</summary>

```c
struct Node{
    int key;
    Node *left, *right;
    Node(int x){
        this->key = x;
        this->left = NULL;
        this->right = NULL;
    }
}
```
</details>

## Insert in BST
- insertion always happens at the bottom, that is it becomes the left.
- only, when the tree is empty the root is updated, it is updated from a NULL to valid node address.

```c
/*iterative solution */
Node* insertBST(Node* root, int key) {
    if (root == NULL) {
        return new Node(key);
    }

    Node* ptr = root;
    Node* prev = NULL;

    while (ptr != NULL) {
        if (key == ptr->key) {
            return root; // Key already exists, no insertion
        }
        prev = ptr;
        if (key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }

    if (key < prev->key)
        prev->left = new Node(key);
    else
        prev->right = new Node(key);

    return root;
}


/* recursive solution */
Node *insertBST(Node *root, int key){
    if(root==NULL)
        return new Node(key);
    else if(key < root->val)
        root->left = insertBST(new Node(key));
    else
        root->right = insertBST(new Node(key));
    return root; // this case will be hit when root->key == key
}

```

## Search in BST

```c
/* tc O(h) sc: O(1) */
bool searchBST(Node *root, int key){
    Node *ptr = root;
    while(ptr!=NULL){
        if(ptr->val == key){
            return true;
        }
        else if(key < ptr->val){
            ptr = ptr->left;
        }
        else{
            ptr =  ptr->right;
        }
        return false;
    }
}

/*same approch using recursion - tc O(h) sc: O(h)*/

bool search(Node* root, int key){
    if(root->key == key)
        return true;
    else if(key < root->key)
        search(root->left, key);
    else
        search(root->right, key);
    return false;
}

```




