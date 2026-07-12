## 1. Delete Nth node from the end

```cpp
void deleteNthNodeFromEnd(int n) {
    if (!head || n <= 0) return;

    Node* fast = head;
    Node* slow = head;

    // Move fast pointer N steps ahead
    for (int i = 0; i < n; i++) {
        // If n is greater than the number of nodes
        if (!fast) return; 
        fast = fast->next;
    }

    // Case 1: If fast reached nullptr, we need to delete the head node
    if (!fast) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Case 2: Move both pointers until fast reaches the last node
    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow->next is the node to be deleted
    Node* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
}

```

## 2. deleteAtPosition()

```cpp
void deleteAtPosition(int position) {
    if (!head || position < 1) return;

    if (position == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    Node* prev = nullptr;
    int count = 1;

    while (current && count < position) {
        prev = current;
        current = current->next;
        count++;
    }

    if (!current) return;

    prev->next = current->next;
    delete current;
}

```

## 4. deleteValue()

```cpp
void deleteValue(int value) {
    if (!head) return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    while (current && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (!current) return;

    prev->next = current->next;
    delete current;
}

```

## 1. deleteHead()

```cpp
void deleteHead() {
    if (!head) return;

    Node* temp = head;
    head = head->next;
    delete temp;
}

```

## 5. deleteTail()

```cpp
void deleteTail() {
    if (!head) return;

    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }

    Node* current = head;
    while (current->next->next) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
}

```