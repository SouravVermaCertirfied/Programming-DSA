#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;

    // Function declaration (no definition yet)
    void introduce();
};

// Function definition outside the class
void Person::introduce() {
    cout << "Hi, my name is " << name << " and I am " << age << " years old." << endl;
}

int main() {
    Person p;
    p.name = "Alice";
    p.age = 25;

    p.introduce();  // Calls the function
    return 0;
}
