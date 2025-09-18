# 1. Hashing
- Hashing provides (Search, Insert and Delete ) operations in **O(1)** on average.  
- Used to implement key-value pairs  (like dictionary).  
- All the values are unique in hash-table.  
- Hashing beats all other DS in doint SID operations in time complexity.  
- O (log N) time is taken by AVL trees, hashing still beats it.

### 1.1 Limitations :  
- like printing values in sorted format // AVL tree does good job here
- storing data in sorted way // AVL tree does good job here
- finding closest values

### 1.2 Applications of Hashing :
- May be second most DS, only after arrays.
- Dictonaries - DB Inexing - Cryptography, Caches.
- Symbol tables in Compiler / Interpreters.  

## 2. DSA questions :


## 3. Direct Access Table
Senario - You have 1000 keys with values from 0 to 999, how to implement S-I-D ?  
Below code can also be modifed for say 1000 to 1999 keys.  
All the operations can be done in O(1) time.  
**Limitations of such approch : if the keys are large values (array size become very big eg phone numbers), strings or floating points.**
```c
bool arr[1000] = {false}; // set all to false
insert(10); // function should set 10th index to 10 and make it true
search(10); // should check if true/false is present at 10th index
delete(10); // function should reset the value at index 10th index
```

## 4. Hashing 
💡 The idea is : take a large universe of keys, use a hash function and covert the value into an index, that index can be used in the smaller array (this array is called hash table).  


## 4.1 How to select a hash function ?  
- Should map a large key to small key (index).  
- Should be fast, O(1) for intergers, O(len) for strings.
- Should generate values from 0 to N-1.
- Hash table side is propotional to input universe.
- **Should uniformaly distribute large keys in hash slots**.

## 4.1.1 Load Factor  
It is the measure of how full the hash table is.  
It is usefull when deciding **re-hashing**. if usually
**Load fact(LF) = No of Stored Elements / No of buckets in the hash table**  
- If load factor is low(much less than 1), means hash table sparse, lower collisions and higher lookup.
- if load factor is high(close or greater than 1) , means hash table is full, means higher collisoion and higher time to search.
- Load factor is 
- Assuming uniform distribution of hash function:
    - Time Complexity to Search : O ( 1 + LF ) // 1 for has function
    - Time Complexity to Insert/Delete : O ( 1 + LF )



## 4.2 Examples of hashing function:  
1. fun(large_key) = large_key % m. *(usually this is taken as prime number close to size of the size of hash table).*
2. For strings, weighted sum. str[]="abcd". *(the function should have some weight to the position of the alphabet, other wise 'abcd' will have same value as 'dcba', hence having more collissions).*
3. Universal Hashing : There are a group of hashfunction and we pick a function randomly and use it hash the table.

# 5. Collision Handling Techniques


- Prefect Hashing : if there keys are known in advance. Eg words in an english language.
- Collision Addressing : ➡️ Chaining ➡️ Probing : Liner Probing, Quadratic Probing and Double hashing.

## 5.1 Chaining
- Chaining is implemented using Linked list, dynamic size array or cell balancing Binary tree.
- **Data structures for storing chains:**
    1. Linked List : Non-cache friendly : O(l) for search, insert and delete.
    2. Dynamic Sized Arrays : Cache Friendly
    3. Self-Balancing BST : Non cache friendly (AVL Tree, Red-Black Tree) O(log l) for search, insert and delete.
```txt
/*using self balancing tree*/
+-------------------------+
|      Hash Table         |
+-------------------------+
|  0 | [ Empty ]          |
|  1 | [ Tree ] ────────┐
|  2 | [ Empty ]        │
|  3 | [ Tree ] ─────┐  │
|  4 | [ Empty ]     │  │
+-------------------------+
                      │  │
        ┌─────────────┘  └─────────────┐
        ▼                              ▼

   Tree at Index 1                Tree at Index 3
        40                             70
       /  \                           /  \
     25    50                       60    80
    /                                 \
  20                                  65

```

