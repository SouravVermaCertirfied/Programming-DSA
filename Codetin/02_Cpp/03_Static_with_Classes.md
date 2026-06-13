# `static`

**Static Data Members:**  
- Shared among all objects of the class.
- Defined outside the class.
- Initialized only once, regardless of the number of objects created.

**Static Member Functions:**
- Can access only static data members and other static functions.
- Do not have access to the this pointer.
- Can be called using the class name.

## Example **Static Data Members:**  

```cpp
#include<iostream>
using namespace std;

class Player {
public:
    static int count; // Declaration of static data member

    Player() { count++; }  // Increment count when a player is created
    ~Player() { count--; } // Decrement count when a player is destroyed
};

int Player::count = 0; // Definition of static data member

int main() {
    Player p1;  // Creating the first player
    cout << Player::count << " "; // Accessing static member using class name
    
    Player p2;  // Creating the second player
    cout << Player::count << " "; // Accessing static member again
    
    return 0;
}
```
## Example **Static Member Functions:**
```cpp
#include<iostream>
using namespace std;

class Player {
private:
    static int count;

public:
    Player() { count++; }
    ~Player() { count--; }

    static int getCount() { return count; } // Static member function
};

int Player::count = 0;

int main() {
    Player p1, p2;
    cout << Player::getCount() << " "; // Accessing static function using class name

    return 0;
}
```

---
<p align="left"><a href="02_OperatorOverloading.md">← 02_OperatorOverloading.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="04_ExceptionHandling.md">04_ExceptionHandling.md →</a></p>