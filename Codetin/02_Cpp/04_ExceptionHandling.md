# Exception Handling
You might wonder, "Why not just use an `if` statement?" 
1.  **Separation of Concerns:** It keeps your "happy path" logic separate from your "error handling" logic.
2.  **Stack Unwinding:** When an exception is thrown, C++ automatically destroys local objects in the scope (calling their destructors), preventing memory leaks. 
3.  **Deep Nesting:** If an error happens 5 functions deep, you can throw it back to `main()` wi

### 1. The Trio: Try, Throw, and Catch

*   **`try`**: This block encloses the code that *might* cause an issue. 
*   **`throw`**: When a problem is detected, you "throw" an exception. This stops the current function and looks for a handler.
*   **`catch`**: This block defines how to react to the specific error thrown.



---

### 2. Basic Syntax
Here is how the structure looks in practice:

<details><summary>Code here</summary>

```cpp
#include <iostream>
#include <string>

int main() {
    try {
        int age = 15;
        if (age < 18) {
            throw 404; // Throwing an integer as an error code
        }
        std::cout << "Access granted.";
    } 
    catch (int errorCode) {
        std::cerr << "Access denied. Error Code: " << errorCode << std::endl;
    }

    return 0;
}
```
</details>

---

### 3. Catch-All Handler
Sometimes you don't know exactly what might go wrong. You can use the "ellipsis" operator `(...)` to catch **any** type of exception. 

> **Note:** This is a "safety valve." Use it sparingly, as it’s usually better to know exactly what failed.

<details><summary>Code here</summary>
```cpp
catch (...) {
    std::cout << "An unknown error occurred!";
}
```
</details>

---

### 4. The Standard Exceptions (`std::exception`)
While you can throw integers or strings, C++ provides a hierarchy of standard exceptions in the `<stdexcept>` header. Using these makes your code more professional and readable.

| Exception | Meaning |
| :--- | :--- |
| `std::runtime_error` | Errors that can only be detected during runtime. |
| `std::out_of_range` | Thrown when accessing elements outside a valid range (like in a `std::vector`). |
| `std::bad_alloc` | Thrown when `new` fails to allocate memory. |
| `std::invalid_argument` | Thrown when an invalid argument is passed to a function. |

---

### 5. Multiple Exceptions

<details><summary>Code here</summary>

```c
#include<iostream>
using namespace std;

int main() {
    double x, y;
    cin >> x >> y;
    try {
        if (x == 0.0)
            throw 0;
        if (y == 0)
            throw string("Y is 0");
        if (x + y < 0.0)
            throw (x + y);
    }
    catch (int e1) {
        cout << e1;
    }
    catch (string &e2) {
        cout << e2;
    }
    catch (...) {
        cout << "x+y < 0";
    }
    cout << "\nBye\n";
    return 0;
}
```
</details>

---

### 6. Exception Handling with functions

<details><summary>Code here</summary>

```c

#include<iostream>
using namespace std;

int average(int arr[], int n) {
    if (n == 0)
        throw string("Array size is 0");
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum / n;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    try {
        int res = average(arr, n);
        cout << res;
    }
    catch (string &e) {
        cout << e;
    }
    cout << "\nBye\n";
    return 0;
}

```
</details>


