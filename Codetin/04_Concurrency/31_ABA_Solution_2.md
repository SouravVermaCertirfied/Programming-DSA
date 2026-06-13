### 2. Hazard Pointers (Memory Safety)
In this approach, we solve ABA by ensuring that a node cannot be freed (and thus reused as "A" again) if any other thread is currently pointing at it.



```c
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

_Atomic(Node*) head = NULL;
_Atomic(Node*) hazard_ptr = NULL; // Simplified: one global hazard pointer

void safe_push(int val) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = val;
    Node* old_head = atomic_load(&head);
    do {
        new_node->next = old_head;
    } while (!atomic_compare_exchange_weak(&head, &old_head, new_node));
}

Node* safe_pop() {
    Node *old_head, *next_node;
    
    while (1) {
        old_head = atomic_load(&head);
        if (!old_head) return NULL;

        // "Mark" this node as being in use
        atomic_store(&hazard_ptr, old_head);

        // Double-check: Did the head change before we marked it?
        if (atomic_load(&head) != old_head) continue;

        next_node = old_head->next;
        if (atomic_compare_exchange_strong(&head, &old_head, next_node)) {
            // Success! Clear the hazard
            atomic_store(&hazard_ptr, NULL);
            return old_head;
        }
    }
}

int main() {
    safe_push(1);
    safe_push(2);
    Node* p = safe_pop();
    if(p) {
        printf("Safely popped: %d\n", p->data);
        // In a real system, you'd check hazard_ptr before calling free(p)
        free(p); 
    }
    return 0;
}
```

---

---
<p align="left"><a href="31_ABA_Solution_1.md">← 31_ABA_Solution_1.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="31_ABA_Solution_3.md">31_ABA_Solution_3.md →</a></p>