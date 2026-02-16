### Syntax
- create a `unordered_set`
```cpp
```cpp
#include <unordered_set>
unordered_set<int> s;
s.insert(10);                // add element
if(s.find(10) != s.end()) {} // element exists
if(s.find(10) == s.end()) {} // element not found
```
- create a `unordered_map`
```cpp
unordered_map<int, int> tbl;
int key = 55;
int val = 54;
tbl[key] = val; // inserting an item
if(tbl.find(key)==tbl.end()) {} // means item not found
if(tbl.find(key)!=tbl.end()) {} // means item is found

```