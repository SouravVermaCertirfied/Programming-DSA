## 5. Delete N-th Node From End
```cpp
void deleteNthNodeFromEnd(int n) {
    if (!head || n <= 0) return;

    Node dummy(0);
    dummy.next = head;

    Node* fast = &dummy;
    Node* slow = &dummy;

    // Advance fast pointer by N steps
    for (int i = 0; i < n; i++) {
        if (!fast->next) return; // n is larger than list size
        fast = fast->next;
    }

    // Move both until fast reaches the last node
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    // slow now sits exactly before the node to delete
    Node* target = slow->next;
    slow->next = target->next;
    head = dummy.next; // Update head (seamlessly handles deleting the original head)
    delete target;
}

```

## 3. Delete At Position (1-based indexing)
```cpp
void deleteAtPosition(int position) {
    if (!head || position < 1) return;

    Node dummy(0);
    dummy.next = head;

    Node* prev = &dummy;
    int count = 1;

    // Advance 'prev' until it sits right before the target position
    while (prev->next && count < position) {
        prev = prev->next;
        count++;
    }

    // If position is out of bounds
    if (!prev->next) return;

    Node* target = prev->next;
    prev->next = target->next; // Skip the target node
    head = dummy.next;         // Update head
    delete target;
}

```
## 4. Delete By Value
```cpp
void deleteValue(int value) {
    if (!head) return;

    Node dummy(0);
    dummy.next = head;

    Node* prev = &dummy;
    // Look for the node whose next node contains the value
    while (prev->next && prev->next->data != value) {
        prev = prev->next;
    }

    // Value found
    if (prev->next) {
        Node* target = prev->next;
        prev->next = target->next; // Link past it
        head = dummy.next;         // Update head
        delete target;
    }
}

```

## 1. Delete Head
```cpp
void deleteHead() {
    if (!head) return;

    Node dummy(0);          // Create dummy node on stack
    dummy.next = head;      // Point dummy to current head

    Node* prev = &dummy;
    Node* current = prev->next; // This is the head node

    prev->next = current->next; // Unlink the head
    head = dummy.next;          // Update actual head pointer
    delete current;             // Free memory
}

```

## 2. Delete Tail
```cpp
void deleteTail() {
    if (!head) return;

    Node dummy(0);
    dummy.next = head;

    Node* prev = &dummy;
    // Move until prev->next is the tail node
    while (prev->next && prev->next->next) {
        prev = prev->next;
    }

    Node* tail = prev->next;
    prev->next = nullptr; // Disconnect tail
    head = dummy.next;    // Update head (handles 1-element list case)
    delete tail;
}

```





