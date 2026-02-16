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
