# Frined Functions
> Friendship is granted, not taken.
The class which has to give friendship decides what it will share, not the class using the frined's shared item.

### Key points:
- Friendship is not inherited
- Frinedship is not translative
- Friendship is not mutual
- Frindship is granted, not taken

A single class member variable CANNOT to be friend, friendship is done at class and function levels.

### Making a function a friend
Example:
```cpp
#include <iostream>
using namespace std;

class Employee; // Forward declaration

class Printer {
public:
    void printEmp(const Employee &e); // Declaration
};

class Employee {
private:
    int id;
    string name;

    // Granting friendship to printEmp function
    friend void Printer::printEmp(const Employee &e);

public:
    Employee(int i, string n) : id(i), name(n) {}
};

void Printer::printEmp(const Employee &e) {
    cout << e.id << " " << e.name << '\n'; // Accessing private members
}

int main() {
    Printer p;
    Employee e(101, "ABC");
    p.printEmp(e); // Output: 101 ABC
    return 0;
}
```

### Making a class a friend

```cpp
#include <iostream>
using namespace std;

class Printer; // Forward declaration

class Employee {
private:
    int id;
    string name;

    // Granting friendship to the Printer class
    friend class Printer;

public:
    Employee(int i, string n) : id(i), name(n) {}
};

class Printer {
public:
    void printEmp(const Employee &e) {
        cout << e.id << " " << e.name << '\n'; // Accessing private members
    }
};

int main() {
    Printer p;
    Employee e(101, "ABC");
    p.printEmp(e); // Output: 101 ABC
    return 0;
}
```