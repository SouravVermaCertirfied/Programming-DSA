# Linked List DSA Tips

## 1. Middle of Linked List
- Use slow and fast pointer, fast pointer running at double the speed of slow pointer.
- If `fast == NULL` → even length
- If `fast != NULL` → odd length (middle node exists)
<details><summary>Code here</summary>

```c 
while(fast || fast->next){
    slow=slow->next; 
    fast = (fast->next ? fast->next->next) : fast->next ; 
} 
``` 
</details>

## 2. Reverse a LL

## 3. Palindrome list
- Find middle - reverse from middle - compare start to mid <=> mid to end.  
- Bring the linked list to orignal state (optional / recommend).

## 4. Intersection of Y linked list  
- **(1 Pass / Two-Pointer):** Use two pointers traversing both lists; switch heads on reaching null so they meet at the intersection.
- **(2 Pass / Length Difference):** Compute lengths of both lists, align the longer list by the difference, then traverse together to find the intersection.
- **Using Hashing:** Store nodes of the first list in a hash set, then traverse the second list to find the first common node. OR  **Brute Force:** Compare every node of the first list with every node of the second list to find the intersection.  
<details><summary>Code here</summary>

```c
#include <stdlib.h>

/* Definition of Node */
struct Node {
    int data;
    struct Node* next;
};

/* -------------------------------------------------- */
/* 1. Optimal (1 Pass) – Two Pointer Traversal */
struct Node* intersectTwoPointer(struct Node* head1, struct Node* head2) {
    if (!head1 || !head2) return NULL;

    struct Node* p1 = head1;
    struct Node* p2 = head2;

    while (p1 != p2) {
        p1 = (p1 == NULL) ? head2 : p1->next;
        p2 = (p2 == NULL) ? head1 : p2->next;
    }
    return p1;
}

/* -------------------------------------------------- */
/* 2. Good (2 Pass) – Length Difference */
struct Node* intersectByLength(struct Node* head1, struct Node* head2) {
    int len1 = 0, len2 = 0;
    struct Node *p1 = head1, *p2 = head2;

    while (p1) { len1++; p1 = p1->next; }
    while (p2) { len2++; p2 = p2->next; }

    p1 = head1;
    p2 = head2;

    int diff = abs(len1 - len2);
    if (len1 > len2) {
        while (diff--) p1 = p1->next;
    } else {
        while (diff--) p2 = p2->next;
    }

    while (p1 && p2) {
        if (p1 == p2) return p1;
        p1 = p1->next;
        p2 = p2->next;
    }
    return NULL;
}

/* -------------------------------------------------- */
/* 3. Using Hashing (conceptual, without actual hash impl) */
struct Node* intersectUsingHashing(struct Node* head1, struct Node* head2) {
    /* 
       Steps:
       1. Insert all nodes of list1 into a hash set
       2. Traverse list2 and return first node found in the set
       (Actual hash implementation omitted for simplicity)
    */
    return NULL;
}

/* -------------------------------------------------- */
/* 4. Brute Force */
struct Node* intersectBruteForce(struct Node* head1, struct Node* head2) {
    struct Node* p1 = head1;
    while (p1) {
        struct Node* p2 = head2;
        while (p2) {
            if (p1 == p2) return p1;
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return NULL;
}
```
</details>
