# Overriding



## 🏛️ C++ Function Overriding: The Essentials

**Function Overriding** allows a derived class to provide a specific implementation of a function already defined in a base class. This is the heart of **Runtime Polymorphism**.

### 1. The Mechanics (How it Works)

- **The VTable (Virtual Table):** A static lookup table created for every class containing virtual functions. It stores the addresses of the functions intended for that class.
- **The vptr (Virtual Pointer):** A hidden pointer added to every **object instance**. It points to the VTable of the object's actual class.
- **Dynamic Binding:** At runtime, the program follows the `vptr` to the `VTable` to find the correct function address. This ensures the behavior matches the **object**, not the **pointer**.

### 2. Requirements for Overriding

- The function in the base class **must** be marked `virtual`.
- The function signatures (name, parameters, and return type) must be **identical**.
- The classes must have an inheritance relationship (`public`, `protected`, or `private`).

### 3. Key Keywords

- `virtual`: Enables dynamic dispatch. Without this, you get "Function Hiding."
- `override`: (C++11) An optional safeguard that ensures you are actually overriding a base function. It catches typos and signature mismatches at compile-time.

---

```c
#include <iostream>
using namespace std;

class Base {
public:
    void show() { // No virtual keyword here!
        cout << "Base version" << endl;
    }
};

class Derived : public Base {
public:
    void show() { 
        cout << "Derived version" << endl;
    }
};

int main() {
    Derived myDerived;
    Base* ptr = &myDerived;

    // Static Binding happens here
    ptr->show(); 
    
    return 0;
}
```

## ❓ FAQ (Your Specific Queries)

**Q: What if a function is made virtual in the base class but not overridden in the child class?**

**A:** The child class inherits the base class's version. In the child class's VTable, the entry for that function will still point to the base class's memory address. The code remains functional, and the "virtual" nature is preserved for future generations (grandchild classes).

**Q: What if I define the function in the child class but do not use the `override` keyword?**

**A:** The code will still work and perform dynamic dispatch (polymorphism) correctly. The `override` keyword is optional. However, omitting it is risky because the compiler won't warn you if you accidentally change the function signature (like changing an `int` to a `float`), which would cause your override to fail silently.

**Q: What if I do not use the `virtual` keyword in the base class?**

**A:** You are no longer performing "Overriding"; you are performing **"Function Hiding."** C++ will use **Static Binding**. If you call the function through a base class pointer, it will execute the base class version, even if the pointer is pointing to a derived object. You lose polymorphic behavior.

---

### 💡 Summary Table

| **Feature** | **virtual + override** | **No virtual** |
| --- | --- | --- |
| **Binding Type** | **Dynamic** (Runtime) | **Static** (Compile-time) |
| **Logic Source** | Determined by the **Object** | Determined by the **Pointer type** |
| **VTable/vptr** | Created and used | Not created |
| **Main Use Case** | Polymorphic behavior (e.g., Games, Plugins) | Simple code reuse/extension |

---
<p align="left"><a href="05_Constructors_CopyCon.md">← 05_Constructors_CopyCon.md</a></p>
<p align="right" style="margin-top:-2.4em;"><a href="08_ExceptionHandlingStackUnWinding.md">08_ExceptionHandlingStackUnWinding.md →</a></p>