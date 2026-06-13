## What is the ABA Problem?
The ABA problem occurs during a **Compare-and-Swap (CAS)** operation. It happens when a thread reads a value $A$, a second thread changes that value to $B$ and then back to $A$, and the first thread finishes its work, sees $A$ again, and assumes nothing has changed.

While the *value* is the same, the *state* of the system might be different (e.g., a node was deleted and a new one was reallocated at the same memory address).

### The Scenario: A Lock-Free Stack
The most common way to demonstrate this is with a linked-list stack.

1.  **Thread 1** wants to pop the top element. It reads the head (Node A) and the next element (Node B).
2.  **Thread 1** is preempted (paused).
3.  **Thread 2** pops Node A, pops Node B, and then pushes Node A back onto the stack.
4.  **Thread 1** resumes. It sees the head is still Node A. It performs a CAS, succeeds, and sets the head to Node B.
5.  **The Crash:** Node B was already freed or reused by Thread 2! The stack is now corrupted.

<details><summary> Code here </summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

// Atomic Compare and Swap wrapper
int compare_and_swap(Node** addr, Node* old_val, Node* new_val) {
    return __sync_bool_compare_and_swap(addr, old_val, new_val);
}

void push(int val) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = val;
    do {
        new_node->next = head;
    } while (!compare_and_swap(&head, new_node->next, new_node));
}

void* thread1_func(void* arg) {
    Node* old_head = head;
    Node* next_node = old_head->next;

    printf("Thread 1: Read head A (%p), next is B (%p)\n", old_head, next_node);
    
    // Simulate preemption: Let Thread 2 mess things up
    sleep(2); 

    if (compare_and_swap(&head, old_head, next_node)) {
        printf("Thread 1: CAS Success! Head is now B (%p). (This is the ABA bug!)\n", next_node);
    } else {
        printf("Thread 1: CAS Failed.\n");
    }
    return NULL;
}

void* thread2_func(void* arg) {
    sleep(1); // Ensure Thread 1 reads first
    
    // Pop A
    Node* A = head;
    head = A->next;
    printf("Thread 2: Popped A\n");

    // Pop B
    Node* B = head;
    head = B->next;
    printf("Thread 2: Popped B and freed it\n");
    free(B); 

    // Push A back
    A->next = head;
    head = A;
    printf("Thread 2: Pushed A back. Stack head is A again.\n");

    return NULL;
}

int main() {
    push(3); // Node C
    push(2); // Node B
    push(1); // Node A

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
```
</details>

## Why Locks Prevent It (Mutex based approach)
In a lock-based approach, the "A" in the sequence is protected by a mutual exclusion primitive (like a `mutex`).

* **Exclusive Access:** When Thread 1 is working on a shared resource, it holds the lock.
* **Prevention of Interleaving:** Thread 2 cannot intervene to change the value from $A \rightarrow B \rightarrow A$ because it is blocked from accessing the data until Thread 1 releases the lock.
* **Atomic Transactions:** Because the entire "Read-Modify-Write" cycle is wrapped in a lock, it becomes a single atomic transaction relative to other threads. There is no window for a "stealthy" change to occur.

### Comparison Table

| Feature | Lock-Based Approach | Lock-Free (CAS) Approach |
| :--- | :--- | :--- |
| **Primary Mechanism** | Mutex / Semaphores | Atomic CAS / Load-Link Store-Conditional |
| **ABA Vulnerability** | **No** | **Yes** |
| **Reason for Safety** | Prevents other threads from touching data during the operation. | Allows other threads to touch data; only checks if the final value matches the start. |
| **Performance Cost** | Thread contention and context switching overhead. | Potential for high retries (spinning) under heavy contention. |

---

## How Lock-Free Systems Fix It
Since lock-free systems can't use locks to hide the "B" transition, they use other techniques to ensure $A$ hasn't been tampered with:
1.  **Hazard Pointers:** Threads flag the nodes they are currently using so they aren't deleted or reused prematurely.
2.  **Version Tagging (Double CAS):** Instead of just checking value $A$, the CPU checks a pair: $(A, \text{version})$. Even if the value returns to $A$, the version number will have incremented to $A+1$.
3.  **LL/SC (Load-Link / Store-Conditional):** A hardware-level approach where the processor tracks if the memory address has been accessed by *any* other instruction since the last load.


The ABA problem is notoriously tricky because it’s a logic error, not a syntax error. To solve it, we need to ensure that the "identity" of the state is tracked, not just the "value" of the pointer.

Here is how you would implement the three primary solutions in C.

---
<p align="left"><a href="30_ThreadSafeDataStructure.md">← 30_ThreadSafeDataStructure.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="31_ABA_Solution_0.md">31_ABA_Solution_0.md →</a></p>