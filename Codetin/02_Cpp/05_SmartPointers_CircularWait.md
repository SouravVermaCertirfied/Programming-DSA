# 1. Circular Dependency Leak

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

<br>

# 2. Explicit Type Handling with `weak_ptr`

### In this example, notice how we transition from a state of "observation" (`weak_ptr`) to "temporary ownership" (`shared_ptr`).

```cpp
#include <iostream>
#include <memory>

struct Computer {
    void boot() { std::cout << "System booting...\n"; }
};

int main() {
    // 1. Create the observer
    std::weak_ptr<Computer> weakMachine;

    {
        // 2. Create the actual owner
        std::shared_ptr<Computer> sharedMachine = std::make_shared<Computer>();
        
        // Point the observer to the object
        weakMachine = sharedMachine;

        // 3. To use it, we MUST create a temporary shared_ptr
        // lock() returns a std::shared_ptr<Computer>
        std::shared_ptr<Computer> tempLock = weakMachine.lock();

        if (tempLock != nullptr) {
            std::cout << "Lock acquired. Object exists.\n";
            tempLock->boot();
        }
        
    } // sharedMachine goes out of scope here. The Computer is deleted.

    // 4. Attempting to lock after the owner is gone
    std::shared_ptr<Computer> secondLock = weakMachine.lock();

    if (secondLock == nullptr) {
        std::cout << "Lock failed. The Computer was already deallocated.\n";
    }

    return 0;
}
```

---

### Why the full types matter here:

1.  **`std::shared_ptr<T> tempLock = weakMachine.lock();`**
    This line is the most important. It shows that `lock()` is an **atomic operation** that produces a strong pointer. If `weakMachine` was about to expire on another thread, `lock()` would either succeed fully or return `nullptr`.
    
2.  **`std::weak_ptr<T>` cannot use `->`**
    If you try to write `weakMachine->boot()`, the compiler will throw an error. This is a safety feature. It forces you to acknowledge that the object might be gone.

3.  **The `nullptr` check**
    Because `secondLock` is an explicit `std::shared_ptr`, comparing it to `nullptr` is the standard way to verify if the "upgrade" from a weak pointer to a shared pointer actually worked.

<br>

# 3. Real World Challenge to Guage the understanding
Ready to test your knowledge? Imagine you are building a **Music Streaming App**.

* **The Library:** A central object that holds all the `Song` objects. It should "own" them.
* **The Playlist:** A list of songs. A song can be in many playlists at once. If the Library deletes a song, the Playlist should know it's gone.
* **The Player:** Needs to hold the "Current Song" while it's playing.

**Which smart pointer would you use for each?**
1.  **Library:** `std::vector<std::_______<Song>>`
2.  **Playlist:** `std::vector<std::_______<Song>>`
3.  **Current Song in Player:** `std::_______<Song>`