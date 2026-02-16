#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<char, int> tbl;

    // 1️⃣ operator[]
    // - Inserts a new element if key doesn't exist (default-initialized value, then assigned).
    // - If the key already exists, overwrites the old value.
    tbl['a'] = 1;  

    // 2️⃣ insert(pair)
    // - Inserts only if the key does NOT already exist.
    // - If the key exists, does nothing (keeps old value).
    tbl.insert({'b', 2});

    // 3️⃣ emplace()
    // - Like insert(), but constructs the element in place (avoids temporary objects).
    // - Does NOT overwrite existing elements.
    tbl.emplace('c', 3);

    // 4️⃣ insert_or_assign()  (C++17+)
    // - Inserts a new element if the key does not exist.
    // - Otherwise, updates (assigns) the new value.
    tbl.insert_or_assign('d', 4);

    // 5️⃣ try_emplace()  (C++17+)
    // - Inserts only if the key does not exist.
    // - Unlike emplace(), the value is constructed only if insertion actually happens.
    //   (Avoids unnecessary construction.)
    tbl.try_emplace('e', 5);

    // Let's show what’s in the map
    for (auto& p : tbl)
        cout << p.first << " : " << p.second << endl;

    // Testing duplicate insertion behavior
    tbl.insert({'b', 22});          // Won’t change 'b' (insert does nothing if key exists)
    tbl['a'] = 11;                  // Overwrites 'a'
    tbl.emplace('c', 33);           // Does nothing (key exists)
    tbl.insert_or_assign('d', 44);  // Updates 'd'
    tbl.try_emplace('e', 55);       // Does nothing (key exists)

    cout << "\nAfter duplicate insertions:\n";
    for (auto& p : tbl)
        cout << p.first << " : " << p.second << endl;

    return 0;
}