```markdown
Usually **no**. In interviews, Qualcomm (and most companies) will default to **singly linked lists** unless the problem explicitly says otherwise.

The reason is that singly linked lists test pointer manipulation skills more effectively:

```c
struct ListNode {
    int val;
    struct ListNode* next;
};
```

With only a `next` pointer, you need to think carefully about:

* Deletion
* Reversal
* Finding predecessors
* Fast/slow pointer techniques
* Dummy nodes

---

## When Doubly Linked Lists Appear

A doubly linked list node looks like:

```c
typedef struct Node {
    int val;
    struct Node* prev;
    struct Node* next;
} Node;
```

Interviewers typically use them in:

### 1. LRU Cache

This is the most common doubly-linked-list question.

Operations must be O(1):

```text
get(key)
put(key)
```

Typical solution:

```text
Hash Map + Doubly Linked List
```

Why doubly linked?

Because you can remove a node in O(1):

```c
node->prev->next = node->next;
node->next->prev = node->prev;
```

without searching for the predecessor.

---

### 2. Browser History / Undo-Redo

```text
A <-> B <-> C <-> D
```

Need:

* move back
* move forward

Doubly linked list is natural.

---

### 3. Design Questions

Sometimes:

> Design a playlist.
>
> Design a scheduler.
>
> Design an MRU/LRU cache.

Then you may choose a doubly linked list.

---

## What Qualcomm Interviewers Actually Care About

They care much more about whether you understand:

### Pointer manipulation

```c
curr->next = prev;
```

### Memory management

```c
malloc
free
```

### Complexity

```text
O(n)
O(1)
```

### Edge cases

```text
NULL
single node
head removal
tail removal
```

than whether you use a doubly linked list.

---

## One Thing Worth Memorizing

For a doubly linked list:

### Insert

```c
newNode->next = curr->next;
newNode->prev = curr;

curr->next->prev = newNode;
curr->next = newNode;
```

### Delete

```c
curr->prev->next = curr->next;

if (curr->next)
    curr->next->prev = curr->prev;
```

This is basically all the pointer manipulation you need.

---

## If the Interviewer Says "Use Any Data Structure"

A good rule is:

| Requirement                  | Use                           |
| ---------------------------- | ----------------------------- |
| Sequential traversal         | Singly linked list            |
| Need previous node often     | Doubly linked list            |
| O(1) delete given node       | Doubly linked list            |
| LRU cache                    | Doubly linked list + hash map |
| Standard linked-list problem | Singly linked list            |

For Qualcomm software/firmware interviews, I'd expect **10 singly-linked-list questions before I expect 1 doubly-linked-list question**. If you're short on prep time, spend 90% of your linked-list study on singly linked lists and just learn the basic insertion/deletion operations for doubly linked lists.

```