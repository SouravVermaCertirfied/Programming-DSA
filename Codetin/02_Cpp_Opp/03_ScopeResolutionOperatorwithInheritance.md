In C++, **Multiple Inheritance** occurs when a class is derived from more than one base class. Ambiguity arises when two or more base classes contain a member (variable or function) with the same name, and the derived class tries to access it.

The compiler won't know which version to use and will throw a compile-time error unless you provide specific instructions.

---

## 1. The Conflict Scenario
Imagine two parent classes, `Scanner` and `Printer`, both having a function named `powerOn()`. If a `Copier` class inherits from both, calling `powerOn()` creates a conflict.

<details><summary> Code here </summary>

```cpp
class Scanner {
public:
    void powerOn() { std::cout << "Scanner powering up..."; }
};

class Printer {
public:
    void powerOn() { std::cout << "Printer powering up..."; }
};

class Copier : public Scanner, public Printer {
    // Inherits both powerOn() functions
};
```
</details>

If you try to call `myCopier.powerOn()`, the compiler will fail because the call is **ambiguous**.

---

## 2. Solution: Scope Resolution Operator
The most direct way to fix this is to explicitly tell the compiler which class's scope to look into using the `::` operator.

### Manual Resolution at Call Site
You can specify the parent class when calling the function from an object:

```cpp
int main() {
    Copier myCopier;
    
    // myCopier.powerOn(); // ERROR: Ambiguous
    
    myCopier.Scanner::powerOn(); // Correct: Calls Scanner's version
    myCopier.Printer::powerOn(); // Correct: Calls Printer's version
}
```

### Internal Resolution (Within the Class)
You can also resolve the ambiguity inside the derived class so that users of the class don't have to deal with the syntax:

```cpp
class Copier : public Scanner, public Printer {
public:
    void powerOn() {
        Scanner::powerOn(); // Decide to default to Scanner's logic
    }
};
```

---

## 3. The "Diamond Problem" and Virtual Inheritance
A more complex version of ambiguity happens when two classes inherit from the same grand-parent class, and then a fourth class inherits from both of them. This creates a "Diamond" shape.



In this case, the bottom class gets **two separate copies** of the grand-parent's variables. To fix this, C++ uses **Virtual Inheritance**.

```cpp
class PoweredDevice { /* ... */ };

// Use 'virtual' to ensure only one copy of PoweredDevice exists
class Scanner : virtual public PoweredDevice { /* ... */ };
class Printer : virtual public PoweredDevice { /* ... */ };

class Copier : public Scanner, public Printer {
    // Only one instance of PoweredDevice is inherited here
};
```

---

## Summary of Solutions

| Method | Use Case |
| :--- | :--- |
| **Scope Resolution (`::`)** | When two different parent classes have a name clash. |
| **`using` Declaration** | To bring a specific parent's member into the derived class scope. |
| **Virtual Inheritance** | When multiple paths lead back to the same common base class (Diamond Problem). |

Are you currently troubleshooting a specific compiler error related to inheritance, or are you designing a class hierarchy from scratch?