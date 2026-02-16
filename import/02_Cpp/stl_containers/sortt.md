# `Sort()` in cpp

- uses `#include<algorithm>`
- Default sorting is acending
- can be changed to decending
- or user defined function also

### 1. Basic syntax
` sort(arr.begin(), arr.end());`
-   first argument is start pointer form which the sorting has to be done.
- second argument is 1 plus last pointer till which sorting has to be done.
- <span style="color: red;">these arugments can be used to sort it partially as well.</span>


### 2. Sorting in decrement order
`sort(arr.begin(), arr.end(), greater<int>())`
- Last arguement is used to decrement it.

### 3. Custom function
- custom comparator function to be used.
- it can also take lambda function - see at the last
- ***Syntax*** `bool cmp(const T &a, const T &b);`
- ```cpp
    if   (cmp(a, b)) {
        // treat a as "less than" b
    }
```


### Exmpales with class:
```cpp  
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

struct Person {
    char name[10];
    int age;
};

bool custAgeCompare_Accending(const Person &a, const Person &b) {
    return a.age < b.age;
}

bool custAgeCompare_Decending(const Person &a, const Person &b) {
    return a.age > b.age;
}

int main() {
    vector<Person> persons = {
        {"Bob", 25},
        {"Alice", 50},
        {"John", 35},
        {"Ron", 55}
    };

    sort(persons.begin(), persons.end(), custAgeCompare_Accending);

    // Print results to verify sorting
    for (const auto &p : persons) {
        cout << p.name << " - " << p.age << endl;
    }

    sort(persons.begin(), persons.end(), custAgeCompare_Decending);

    // Print results to verify sorting
    for (const auto &p : persons) {
        cout << p.name << " - " << p.age << endl;
    }


    return 0;
}

```

### More exmpale - using struct
```cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

struct Person {
    char name[10];
    int age;
};

// Define a comparator as a separate class (functor)
struct AgeComparator {
    int minAge;

    // Constructor to set context value
    AgeComparator(int minAge) : minAge(minAge) {}

    // Overload the function call operator
    bool operator()(const Person &a, const Person &b) const {
        // If one of them is under minAge, don't move them
        if (a.age < minAge || b.age < minAge)
            return false;
        return a.age < b.age;
    }
};

int main() {
    vector<Person> persons = {
        {"Bob", 25},
        {"Alice", 50},
        {"John", 35},
        {"Ron", 55}
    };

    // Create a comparator object with extra context
    AgeComparator comp(30);

    sort(persons.begin(), persons.end(), comp);

    for (const auto &p : persons) {
        cout << p.name << " - " << p.age << endl;
    }

    return 0;
}

```

**using lambda function**

```cpp
int minAge = 30;
sort(persons.begin(), persons.end(),
     [minAge](const Person &a, const Person &b) {
         // Compare only people older than minAge
         if (a.age < minAge || b.age < minAge) return false;
         return a.age < b.age;
     });

```