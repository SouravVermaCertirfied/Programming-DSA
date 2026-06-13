### References vs Pointers
1. A pointer can be declared as VOID but a reference can't. It must refer to some existing variable/memory location. Also, references can't be assigned NULL unlike pointers.  
2. References are less powerful than pointers:  
    - Once a Reference is created, it can't be made to refer another variable. With pointers we can do so.
    - A reference must be initialized. Pointers can be declared without initialization.

### Types of Function Call (References v/s Pointers)
There are 3 ways to pass C++ arguments to a function:  
1. call-by-reference with pointer argument
2. call-by-reference with reference argument

### WAP : Usage of References 
Here the calling function does not use any operator with the variable. But the function defination has '&'.
<details><summary>Code here</summary>

```cpp
#include<iostream>
using namespace std;
void fun(int a, int &b, int *c){
    a += 1;
    b += 1;
    *c += 1;
    return;
}

int main(){
    int a = 10, b = 10, c=10, d=10;
    int &p = d; // It creates an alias, meaning p and d are the same memory location
    p++;
    fun(a, b, &c);
    // a is 10 ; b is 11 ; c is 11 ; d is 11
    return 0;
}
```
</details>

### WAP : Modify vector using References 

<details><summary>Code here</summary>

```cpp
vector<int> vect{10, 20, 30};
for( int x : vect) // is a copy of the variable
    x = x + 5; // Oringal array is not changed
for( int &x : vect) // x is the alias of variable
    x = x + 5; // Orignal array gets changed
```
</details>

---
<p align="left"></p>
<p align="right" style="margin-top:-2.4em;"><a href="02_FriendKeyword.md">02_FriendKeyword.md →</a></p>