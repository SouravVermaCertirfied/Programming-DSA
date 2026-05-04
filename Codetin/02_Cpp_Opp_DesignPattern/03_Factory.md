The **Factory Method Pattern** is the natural next step after the Singleton. While the Singleton is about *limiting* instances, the Factory is about *delegating* the responsibility of creating them.

In C++, we use this when we have a base class and several derived classes, but we don't want the "client" (the main part of your code) to worry about the specific logic of which derived class to instantiate.

---

### The Concept
Imagine you are building a game with different types of enemies. Instead of using a giant `if-else` or `switch` block every time you want to spawn an enemy, you call a "Factory."



---

### C++ Implementation
To implement this properly in C++, we use **Polymorphism** (virtual functions) and **Smart Pointers** (to manage memory safely).

```cpp
#include <iostream>
#include <memory>
#include <string>

// 1. The Product Interface
class Enemy {
public:
    virtual void attack() = 0; // Pure virtual function
    virtual ~Enemy() = default; // Virtual destructor is CRUCIAL in OOP
};

// 2. Concrete Products
class Ghost : public Enemy {
public:
    void attack() override { std::cout << "Ghost fades in and scares you!\n"; }
};

class Zombie : public Enemy {
public:
    void attack() override { std::cout << "Zombie bites you!\n"; }
};

// 3. The Factory (Creator)
class EnemyFactory {
public:
    // This is the core "Factory Method"
    static std::unique_ptr<Enemy> createEnemy(const std::string& type) {
        if (type == "ghost") {
            return std::make_unique<Ghost>();
        } else if (type == "zombie") {
            return std::make_unique<Zombie>();
        }
        return nullptr;
    }
};

int main() {
    // The client code doesn't know about Ghost or Zombie classes directly.
    // It only knows it wants an "Enemy" of a certain type.
    auto myEnemy = EnemyFactory::createEnemy("ghost");

    if (myEnemy) {
        myEnemy->attack();
    }

    return 0;
}
```

---

### Why use this in C++?

1.  **Loose Coupling:** Your `main()` function doesn't need to `#include "Ghost.h"` or `#include "Zombie.h"`. It only needs the Factory and the Base class.
2.  **Single Responsibility Principle:** The creation logic is moved to one place. If you add a "Vampire" later, you only change the Factory, not the rest of your app.
3.  **Memory Management:** By returning a `std::unique_ptr`, the Factory tells the caller: "I created this for you; you own it now, and it will be deleted automatically when you're done."

### Common Pitfall: The Virtual Destructor
In C++, if you have a base class pointer (like `Enemy*`) pointing to a derived object (like `Ghost`), and you delete it, the `~Ghost()` destructor will **not** be called unless the base class destructor is marked `virtual`. This causes memory leaks! Always include `virtual ~Base() = default;`.

