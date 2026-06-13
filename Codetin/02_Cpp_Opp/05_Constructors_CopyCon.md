# What is a Copy Constructor?

A copy constructor is a member function that initializes an object using another object of the same class. Its signature looks like this:
`ClassName(const ClassName &old_obj);`

### Why the `&` (Reference)?

If we passed by value, the compiler would try to make a copy of the object to pass to the constructor... which would call the copy constructor again, leading to **infinite recursion**.

---

## ⚡ The "Rule of Three"

In C++, if your class manages heap memory (like our `char *name`), you **must** implement three things to avoid crashes:

1. **Destructor:** To `delete` the memory.
2. **Copy Constructor:** To perform a **Deep Copy**.
3. **Copy Assignment Operator:** To handle `p2 = p1` after both are already created.

---

## 🧪 Deep Copy vs. Shallow Copy in C++

By default, C++ provides a **default copy constructor** that does a member-wise copy. For pointers, this is a **Shallow Copy**.

### 1. The Danger (Shallow Copy)

If you don't write your own copy constructor:

* `p1.name` and `p2.name` point to the same address.
* When the program ends, `p1`'s destructor deletes the memory.
* When `p2` tries to delete its memory, the program crashes because the memory is already gone (**Double Free Error**).

### 2. The Solution (Deep Copy Constructor)

Here is how you implement it manually to ensure independence:

```cpp
class Person {
public:
    int rollno;
    char *name;

    // Standard Constructor
    Person(int r, const char *n) {
        rollno = r;
        name = new char[strlen(n) + 1]; // C++ uses 'new' instead of 'malloc'
        strcpy(name, n);
    }

    // COPY CONSTRUCTOR (The Trainer)
    Person(const Person &other) {
        rollno = other.rollno;
        // Deep Copy: Allocate new memory for the copy
        name = new char[strlen(other.name) + 1]; 
        strcpy(name, other.name);
        
        printf("Copy Constructor Called! Deep copy created.\n");
    }

    // Destructor
    ~Person() {
        delete[] name; // C++ uses 'delete' instead of 'free'
    }
};

```

---

## 🔍 When is the Copy Constructor triggered?

It isn't just triggered when you think! It happens in three specific scenarios:

1. **Direct Initialization:**
`Person p2 = p1;` or `Person p2(p1);`
2. **Passing by Value:**
`void myFunc(Person p)` — when you call `myFunc(p1)`, a copy is made.
3. **Returning by Value:**
`Person createPerson()` — when the function returns an object.

---

## 🚀 Critical to Know

* **Member-wise copy:** The default behavior. Fine for `int`, disastrous for `char*`.
* **Initialization vs. Assignment:**
> * `Person p2 = p1;` calls the **Copy Constructor** (creating a new object). ☢️☢️☢️
> * `p2 = p1;` (on already existing objects) calls the **Assignment Operator**. ☢️☢️☢️


* **The Const Requirement:** We use `const` in `(const Person &other)` because we promise not to modify the original object while copying it.

---

## ❓ FAQ

**Q: If I use `std::string` instead of `char*`, do I still need a copy constructor?**
**A:** Usually, **no**. `std::string` has its own copy constructor that handles deep copying automatically. This is why modern C++ prefers `std::string` over raw pointers.

**Q: What happens if I forget the `&` in the constructor?**
**A:** The compiler will throw an error: *"copy constructor must pass its first argument by reference"*.

**Q: Can I "disable" copying?**
**A:** Yes! In modern C++, you can write `Person(const Person &other) = delete;`. This is useful for unique objects (like a Database connection) that should never be cloned.

---
<div style="display: flex; justify-content: space-between;">
    <a href="05_Constructors.md">← 05_Constructors.md</a>
    <a href="07_OverridingAndVirtualKeyword.md">07_OverridingAndVirtualKeyword.md →</a>
</div>