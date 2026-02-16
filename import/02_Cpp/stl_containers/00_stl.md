| **Category**                    | **Component / Function**          | **Header File**             | **Description**                                                     |
| ------------------------------- | --------------------------------- | --------------------------- | ------------------------------------------------------------------- |
| **Sequence Containers**         | `pair`                            | `<utility>`                 | Stores two heterogeneous elements (`first`, `second`).              |
|                                 | `array`                           | `<array>`                   | Fixed-size sequential container (C++11+).                           |
|                                 | `vector`                          | `<vector>`                  | Dynamic array with fast random access; auto-resizable.              |
|                                 | `deque`                           | `<deque>`                   | Double-ended queue; fast insertion/removal at both ends.            |
|                                 | `list`                            | `<list>`                    | Doubly linked list; efficient insertion/removal anywhere.           |
|                                 | `forward_list`                    | `<forward_list>`            | Singly linked list (C++11+).                                        |
| **Container Adaptors**          | `stack`                           | `<stack>`                   | LIFO (Last-In-First-Out) adaptor (usually uses `deque`).            |
|                                 | `queue`                           | `<queue>`                   | FIFO (First-In-First-Out) adaptor (usually uses `deque` or `list`). |
|                                 | `priority_queue`                  | `<queue>`                   | Heap-based adaptor; elements sorted by priority.                    |
| **Associative Containers**      | `set`                             | `<set>`                     | Stores unique elements in sorted order.                             |
|                                 | `multiset`                        | `<set>`                     | Stores duplicate elements in sorted order.                          |
|                                 | `map`                             | `<map>`                     | Key–value pairs with unique keys; sorted by key.                    |
|                                 | `multimap`                        | `<map>`                     | Key–value pairs allowing duplicate keys; sorted by key.             |
| **Unordered (Hash) Containers** | `unordered_set`                   | `<unordered_set>`           | Unique elements; stored using hash table (unsorted).                |
|                                 | `unordered_multiset`              | `<unordered_set>`           | Allows duplicate elements; hash-based (unsorted).                   |
|                                 | `unordered_map`                   | `<unordered_map>`           | Key–value pairs with unique keys; hash-based.                       |
|                                 | `unordered_multimap`              | `<unordered_map>`           | Allows duplicate keys; hash-based.                                  |
| **Algorithms**                  | `binary_search()`                 | `<algorithm>`               | Checks if an element exists in a sorted range.                      |
|                                 | `lower_bound()` / `upper_bound()` | `<algorithm>`               | Finds insertion position while keeping range sorted.                |
|                                 | `min()` / `max()`                 | `<algorithm>`               | Returns the smallest or largest element.                            |
|                                 | `reverse()`                       | `<algorithm>`               | Reverses the order of elements in a range.                          |
|                                 | `rotate()`                        | `<algorithm>`               | Rotates elements around a pivot.                                    |
|                                 | `sort()`                          | `<algorithm>`               | Sorts elements in ascending order (default `<`).                    |
|                                 | `swap()`                          | `<utility>` / `<algorithm>` | Swaps two variables or container contents.                          |
