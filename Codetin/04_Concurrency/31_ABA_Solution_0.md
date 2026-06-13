# Solution using each of the approach

### 1. Tagged State (Double-Wide CAS)
This is the most common hardware-level fix. You pair the pointer with a **generation counter**. Even if the pointer returns to "A," the counter will have incremented, causing the CAS to fail.

> **Note:** This requires `atomic_compare_exchange` on a 128-bit structure (on 64-bit systems).



```c
#include <statomic.h>
#include <stdint.h>

typedef struct {
    Node* ptr;
    uintptr_t tag;
} TaggedPointer;

// Assume head is now a _Atomic TaggedPointer
_Atomic TaggedPointer head;

void safe_push(int val) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = val;
    
    TaggedPointer old_head, new_head;
    do {
        old_head = atomic_load(&head);
        new_node->next = old_head.ptr;
        new_head.ptr = new_node;
        new_head.tag = old_head.tag + 1; // Increment the version
    } while (!atomic_compare_exchange_weak(&head, &old_head, new_head));
}
```

---

### 2. Hazard Pointers
Hazard pointers prevent the "B" in the ABA sequence from being deleted or reused while another thread is looking at it. A thread "claims" a pointer by placing it in a global array. Other threads check this array before freeing memory.



```c
#include <stdatomic.h>

_Atomic(Node*) HazardPointers[MAX_THREADS];

Node* safe_pop() {
    Node* temp;
    do {
        temp = atomic_load(&head);
        if (!temp) return NULL;

        // "Announce" we are using this pointer
        atomic_store(&HazardPointers[thread_id], temp);

        // Verify head didn't change while we were announcing
        if (atomic_load(&head) != temp) continue; 

        Node* next = temp->next;
        if (atomic_compare_exchange_strong(&head, &temp, next)) {
            // Success! Clear hazard pointer
            atomic_store(&HazardPointers[thread_id], NULL);
            return temp; 
            // Note: Use a "RetireList" instead of free(temp) immediately
        }
    } while (1);
}
```

---

### 3. Deferred Reclamation (The "GC" approach)
In environments without a Garbage Collector (like standard C), we use **Epoch-based Reclamation**. Memory is only freed when it is certain that no threads are still operating in the "epoch" (time period) during which the memory was removed.

* **Logic:** Instead of calling `free()`, you add the node to a "Retire List."
* **The Check:** Periodically, once all active threads have moved to a new epoch, the "Retire List" from the old epoch is actually freed.

```c
// Conceptual logic for Epoch-based reclamation
void retire_node(Node* n) {
    list_add(retire_lists[current_epoch], n);
    
    if (all_threads_moved_to_next_epoch()) {
        for (Node* node : retire_lists[oldest_epoch]) {
            free(node); // Finally safe to free
        }
    }
}
```

---

### Summary Table

| Approach | Complexity | Performance | Best For... |
| :--- | :--- | :--- | :--- |
| **Tagged Pointers** | Medium | High | Systems supporting 128-bit CAS. |
| **Hazard Pointers** | High | Medium | Systems with limited memory (reclaims fast). |
| **Epoch Reclamation** | High | Very High | High-throughput systems where memory latency matters. |

Which of these approaches feels most applicable to the architecture you're currently working with?

---
<div style="display: flex; justify-content: space-between;">
    <a href="31_ABA_Senario.md">← 31_ABA_Senario.md</a>
    <a href="31_ABA_Solution_1.md">31_ABA_Solution_1.md →</a>
</div>