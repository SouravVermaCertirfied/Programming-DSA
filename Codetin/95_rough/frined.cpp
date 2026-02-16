#include <iostream>
#include <string>
using namespace std;

class Printer; // Forward declaration

class Employee {
private:
    int id;
    string name;

    // Only Printer::printEmp can access private members
    friend void Printer::printEmp(const Employee &e);

public:
    Employee(int i, string n) : id(i), name(n) {}
};

class Printer {
public:
    // Fully defined inside the class
    void printEmp(const Employee &e) {
        cout << e.id << " " << e.name << '\n'; // Can access private members
    }
};

int main() {
    Printer p;
    Employee e(101, "ABC");
    p.printEmp(e); // Output: 101 ABC
    return 0;
}
