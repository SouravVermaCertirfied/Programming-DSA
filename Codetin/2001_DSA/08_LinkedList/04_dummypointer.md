```markdown
## Dummy Pointer Trick

The dummy pointer (or dummy node) trick is one of the most useful techniques for linked lists in C because it eliminates special cases involving the head of the list.

```c
typedef struct Node{
    int val;
    struct Node * next;
} Node;
```
### Example: Delete first occurance of `x`

```c

// should return the head pointer
// D -> 1 -> 2 -> 3 -> NULL
Node *deleteFirstOccurrance(int x, Node *head){
    Node dummy;
    dummy.next = head;

    Node *curr = head;
    Node *prev = &dummy;

    while(curr && curr->val!=x){
        prev = curr;
        curr = curr->next;
    }
    if(curr){
        prev->next = curr->next;
        free curr;
    }
    return dummy.next;

}

```

### Example : Insert at front

```c
// insert at front

Node *insertAtFront(Node *head, int item){

    Node dummy;
    dummy.next = head;

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = item;
    newNode->next = dummy.next;

    dummy.next = newNode;

    return dummy.next; // this is head now

}

```

### Example: Delete all the occurrances of x

```c
// return head
Node* deleteAllOccurrancesOfx(int x, Node* head) {
    Node dummy;
    dummy.next = head;

    Node* prev = &dummy;
    Node* curr = head;

    while (curr) {
        if (curr->val == x) {
            Node* temp = curr;
            prev->next = curr->next;
            curr = curr->next;

            delete temp;   // or free(temp) if malloc was used
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}

```

### Remove dublicates in a sorted list

```c
/*i will delete the current node, if the next node also has the same value*/
Node *removeDublicate(Node *head){
   Node dummy;
   dummy.next = head;

   Node *prev = &dummy;
   Node *curr = head;

   while(curr->next){
        if(curr->val == (curr->next)->val){
            Node *temp = curr;
            prev->next = curr->next;
            curr = curr->next;
            free(temp);
        }
        else{
            prev = curr;
            curr = curr->next;
        }
   }
   return dummy.next;
}

```
```