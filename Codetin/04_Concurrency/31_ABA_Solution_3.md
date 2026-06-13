You're right. To truly demonstrate **Epoch-Based Reclamation (EBR)** in C, we need a way to track when threads enter and exit "critical sections." Memory is only freed when all active threads have moved to a new epoch, guaranteeing no one is still holding a pointer to the old memory.

Here is a functional, simplified implementation of the Epoch approach.

### 3. Epoch-Based Reclamation (EBR)
In this model, we maintain a **global epoch** and a **local epoch** for each thread. Nodes aren't freed; they are placed in a "retirement list" associated with the epoch they were removed in.

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structure to track retired nodes
typedef struct {
    Node* nodes[100];
    int count;
} RetirementList;

// Global State
atomic_int global_epoch = 0;
_Atomic(Node*) head = NULL;

// Thread-local state (simplified for this example)
__thread int local_epoch = -1; 
RetirementList storage[3]; // We need 3 lists to handle overlaps safely

void enter_critical_section() {
    local_epoch = atomic_load(&global_epoch);
}

void leave_critical_section() {
    local_epoch = -1;
}

void retire_node(Node* n) {
    int epoch = atomic_load(&global_epoch);
    RetirementList* list = &storage[epoch % 3];
    list->nodes[list->count++] = n;

    // Periodically try to advance epoch and clean up
    if (list->count >= 5) {
        // In a real system, you'd check if all threads have left the old epoch
        atomic_fetch_add(&global_epoch, 1);
        
        // Clean up the list from 2 epochs ago (now safe)
        RetirementList* old_list = &storage[(epoch - 1) % 3];
        for (int i = 0; i < old_list->count; i++) {
            printf("Epoch Reclamation: Safely freeing node with data %d\n", old_list->nodes[i]->data);
            free(old_list->nodes[i]);
        }
        old_list->count = 0;
    }
}

void push(int val) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = val;
    Node* old_head = atomic_load(&head);
    do {
        new_node->next = old_head;
    } while (!atomic_compare_exchange_weak(&head, &old_head, new_node));
}

Node* pop() {
    enter_critical_section();
    
    Node* old_head = atomic_load(&head);
    while (old_head) {
        Node* next_node = old_head->next;
        if (atomic_compare_exchange_strong(&head, &old_head, next_node)) {
            retire_node(old_head); // Don't free yet!
            leave_critical_section();
            return old_head;
        }
        // old_head is updated by atomic_compare_exchange on failure
    }
    
    leave_critical_section();
    return NULL;
}

int main() {
    push(10);
    push(20);
    push(30);
    push(40);
    push(50);
    push(60);

    printf("Popping elements using Epoch Reclamation...\n");
    for(int i = 0; i < 6; i++) {
        pop();
    }

    return 0;
}
```

---

### Comparison of the 3 Solutions



| Feature | **Tagged Pointers** | **Hazard Pointers** | **Epoch Reclamation** |
| :--- | :--- | :--- | :--- |
| **Primary Fix** | Logic (detects change) | Memory (prevents reuse) | Memory (delays reuse) |
| **Complexity** | Low (if HW supports it) | Very High | Medium/High |
| **Overhead** | Low (Atomic) | High (Per-op writes) | Low (Amortized) |
| **Main Drawback** | Needs 128-bit CAS | Slower `pop` | Memory usage grows until "cleanup" |

### Which one should you use?
* **Use Tagged Pointers** if you are on x86_64 or ARM64 and your compiler supports `__int128` atomics. It’s the fastest and cleanest.
* **Use Hazard Pointers** if memory is extremely tight and you need to free it the *second* it’s no longer used.
* **Use Epochs** for high-performance systems (like Linux kernel RCU or high-end databases) where you want the lowest possible overhead on the "fast path."

---
<div style="display: flex; justify-content: space-between;">
    <a href="31_ABA_Solution_2.md">← 31_ABA_Solution_2.md</a>
    <a href="60_CodingQuestionConcepts.md">60_CodingQuestionConcepts.md →</a>
</div>