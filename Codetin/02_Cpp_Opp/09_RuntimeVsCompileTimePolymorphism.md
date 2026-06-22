# Runtime vs Compile Time Poly

In C++, polymorphism allows objects to be treated as instances of their parent class while behaving according to their actual derived class. The distinction between **Compile-Time** and **Runtime** polymorphism boils down to *when* the compiler decides which function to execute.

---

## 1. Compile-Time Polymorphism (Static Binding)

Also known as **Early Binding**, this occurs when the compiler selects the appropriate function at the time of compilation. This is highly efficient because there is no overhead during the execution of the program.

### Key Mechanisms:

- **Function Overloading:** Multiple functions with the same name but different parameter lists.
- **Operator Overloading:** Giving special meaning to standard operators (like `+` or `<<`) for user-defined types.
- **Templates:** Generating specific code for different data types at compile time.

**Example of Function Overloading:**

C++

```c
void print(int i) { cout << "Integer: " << i << endl; }
void print(double f) { cout << "Float: " << f << endl; }
// The compiler knows which 'print' to call based on the argument type.
```

---

## 2. Runtime Polymorphism (Dynamic Binding)

Also known as **Late Binding**, this occurs when the function to be called is determined while the program is running. This is used when a base class pointer or reference points to a derived class object.

### Key Mechanisms:

- **Virtual Functions:** Functions declared with the `virtual` keyword in a base class.
- **Inheritance:** Overriding base class methods in derived classes.

**How it works:**

The compiler creates a **V-Table** (Virtual Table) for classes with virtual functions. At runtime, the program looks up the correct function address in this table.

**Example of Virtual Functions:**

C++

```c
class Animal {
public:
    virtual void speak() { cout << "Animal sound" << endl; }
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof!" << endl; }
};

// At runtime, this calls Dog's speak(), not Animal's.
Animal* ptr = new Dog();
ptr->speak();
```

---

## Comparison Table

| **Feature** | **Compile-Time Polymorphism** | **Runtime Polymorphism** |
| --- | --- | --- |
| **Alternative Name** | Static / Early Binding | Dynamic / Late Binding |
| **Implementation** | Function/Operator Overloading, Templates | Virtual Functions and Overriding |
| **Execution Speed** | Faster (resolved at compile time) | Slower (overhead of V-Table lookup) |
| **Flexibility** | Less flexible; types must be known | Highly flexible; supports abstraction |
| **Requirement** | Doesn't strictly require inheritance | Requires Inheritance and Virtual functions |

---

### What are the ways to do runtime polymorphism ?

- Mainly in cpp it is with virtual and override keywords
- Function Pointers : The "Old School" C-style way. You can store the address of a function in a pointer and change that address at runtime to point to a different function. **Example:** A `struct` containing a pointer to a function. Different instances of the struct can point to different logic.
- There are other ways but lets not focus on them for now:
    - `std::variant` and `std::visit` (Sum Types)
    - `std::function` and Type Erasure