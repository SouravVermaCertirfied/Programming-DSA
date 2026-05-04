# Constuctors

> In the "Function Style" constructors parameterless because that style has a major limitation: it cannot pass data up to a parent class.

Here is the completed documentation for your notes, filled with the specific code structures you requested.

# Constructors

## 1. Function style Constructors
In this style, member variables are assigned values inside the curly braces `{}` of the constructor.

### 1.1 Example without inheritance
```cpp
class Grandfather {
    private:
        int age;
    public:
        Grandfather(int a) {
            age = a; // Assignment inside body
        }
};
```

### 1.2 Example with inheritance

<details><summary>Code here</summary>

```cpp
#include<iostream>
using namespace std;

class Grandfather {
    public:
        Grandfather() { cout << "Grandfather initialized\n"; }
};

class Father : public Grandfather {
    public:
        Father() { cout << "Father initialized\n"; }
};

class Child : public Father {
    public:
        Child() { 
            // Logic happens here after parents are done
            cout << "Child initialized\n"; 
        }
};
```
</details>

### 1.3 Pros
*   **Ease of Debugging**: You can easily wrap assignments in `if-else` statements or print logs.
*   **Simple Syntax**: It looks like standard procedural code, making it easy for beginners to read.

### 1.4 Cons
*   **Efficiency**: Technically performs "assignment," not "initialization." The object is created with a junk/default value first, then overwritten.
*   **Inheritance Limit**: You cannot pass values to a parent constructor using this style; you can only modify the current class's members.

---

## 2. Initialize list style constructors
Values are initialized using a colon `:` before the constructor body begins.

### 2.1 Example without inheritance
```cpp
class Grandfather {
    private:
        int age;
    public:
        Grandfather(int a) : age(a) { } // Initialized before {}
};
```

### 2.2 Example with inheritance

<details><summary>Code here</summary>

```cpp
#include<iostream>
using namespace std;

class Grandfather {
    int g_id;
    public:
        Grandfather(int id) : g_id(id) {}
};

class Father : public Grandfather {
    int f_id;
    public:
        Father(int g, int f) : Grandfather(g), f_id(f) {}
};

class Child : public Father {
    int c_id;
    public:
        Child(int g, int f, int c) : Father(g, f), c_id(c) {}
};
```
</details>

### 2.3 Pros
*   **High Performance**: Sets the value at the moment of memory allocation.
*   **Parent Communication**: The only way to call a specific (parameterized) constructor of a base class.

### 2.4 Cons
*   **Strict Ordering**: Members are initialized in the order they are declared in the class, regardless of their order in the list.
*   **Complexity**: Can become hard to read if the inheritance chain is very deep with many variables.

---

## 3. Why to use Initializer list
1.  **Required for `const` and `&`**: `const` variables and references *must* be initialized when created; they cannot be assigned values later inside `{}`.
2.  **Avoids Default Constructor Calls**: Without an initializer list, C++ calls the default constructor for all member objects first. The list bypasses this, saving CPU cycles.
3.  **Base Class Control**: It allows a derived class to "reach up" and provide necessary data to its parent and grandparent classes.