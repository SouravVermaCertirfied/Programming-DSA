# Linked List - Find Loop Length

- Find the length of the loop in a linked list.  

```cpp

/* Brute Force - using hashmap*/

unordered_set<Node *> visited;

bool isNotAlreadyPresent(Node *ptr){
    if(visited.find(ptr) == visited.end()){
        visited.insert(ptr);
        return true;
    }
    return false;
}

int findLength_BruteForce(Node *head){
    Node *ptr = head;
    int count = 0;

    while(ptr!=NULL && isNotAlreadyPresent(ptr)){
        ptr = ptr->next;
        count++;
    }
    if(ptr==NULL)
        return 0;

    return count;
}

```