# Circular Dependency Leak

A circular dependency (or "deadly embrace") happens when two objects hold `std::shared_ptr`s to each other. Because each object's reference count stays at least at 1, the memory is never freed, creating a permanent leak.

### The Problem: The Infinite Loop
In the example below, even when `main` finishes, the `Man` and `Woman` objects stay alive in memory because they are keeping each other's reference counts above zero.



```cpp
#include <iostream>
#include <memory>

struct Woman; // Forward declaration

struct Man {
    std::shared_ptr<Woman> wife;
    ~Man() { std::cout << "Man deleted\n"; }
};

struct Woman {
    std::shared_ptr<Man> husband;
    ~Woman() { std::cout << "Woman deleted\n"; }
};

int main() {
    auto m = std::make_shared<Man>();
    auto w = std::make_shared<Woman>();

    m->wife = w;    // w count = 2
    w->husband = m; // m count = 2

    return 0; 
    // m and w go out of scope, counts drop to 1.
    // Nothing is deleted! Memory is leaked.
}
```

---

### The Solution: `std::weak_ptr`
To fix this, we make one of the pointers "weak." A `weak_ptr` allows you to see the object, but it **does not increase the reference count**. 



```cpp
// Replace below implementation in the above code
struct Woman {
    // Changing this to weak_ptr breaks the cycle
    std::weak_ptr<Man> husband; 
    ~Woman() { std::cout << "Woman deleted\n"; }
};
```

**What happens now:**
1. `main` ends. `m` is destroyed.
2. Since `Woman` only held a `weak_ptr` to `Man`, the reference count for `Man` actually hits 0.
3. `Man` is deleted, which destroys his `shared_ptr` to `Woman`.
4. Now `Woman`'s count hits 0, and she is deleted too. **Success!**

---

### When to use this?
A good rule of thumb is to look at the **Hierarchy**:
* **Parent to Child:** Use `std::shared_ptr` (The parent "owns" or "keeps alive" the child).
* **Child to Parent:** Use `std::weak_ptr` (The child knows the parent exists but doesn't "own" them).

Does that logic of "breaking the cycle" make sense, or would you like to see how to actually use a `weak_ptr` to access data (since you can't use `->` directly on it)?