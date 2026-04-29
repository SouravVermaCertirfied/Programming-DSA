Since C doesn't have a built-in Garbage Collector or a high-level framework for Hazard Pointers, implementing these "fully" in a single snippet requires a bit of scaffolding.

Below are the complete, runnable examples for **Tagged Pointers** (the hardware approach) and a simplified **Hazard Pointer/Epoch** logic.

---

### 1. Tagged Pointers (Double-Wide CAS)
This is the most "correct" way to solve ABA in C on modern x86_64 CPUs. We use a `struct` that fits into 16 bytes and use `__atomic` built-ins to swap the pointer and a counter simultaneously.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// A 16-byte structure (on 64-bit) to hold pointer + version
typedef struct {
    Node* ptr;
    uintptr_t tag;
} TaggedPointer;

// Global head
_Atomic TaggedPointer head = { .ptr = NULL, .tag = 0 };

void push(int val) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = val;
    
    TaggedPointer old_head, new_head;
    
    do {
        // Load the current head and its version tag
        old_head = __atomic_load_n(&head, __ATOMIC_RELAXED);
        new_node->next = old_head.ptr;
        
        new_head.ptr = new_node;
        new_head.tag = old_head.tag + 1; // Increment tag to prevent ABA
        
    } while (!__atomic_compare_exchange(&head, &old_head, &new_head, false, 
                                        __ATOMIC_RELEASE, __ATOMIC_ACQUIRE));
}

Node* pop() {
    TaggedPointer old_head, new_head;
    
    do {
        old_head = __atomic_load_n(&head, __ATOMIC_RELAXED);
        if (old_head.ptr == NULL) return NULL;
        
        new_head.ptr = old_head.ptr->next;
        new_head.tag = old_head.tag + 1; // Incrementing tag ensures uniqueness
        
    } while (!__atomic_compare_exchange(&head, &old_head, &new_head, false, 
                                        __ATOMIC_RELEASE, __ATOMIC_ACQUIRE));
                                        
    return old_head.ptr;
}

int main() {
    push(10);
    push(20);
    Node* n = pop();
    if(n) printf("Popped: %d\n", n->data);
    return 0;
}
```

---
