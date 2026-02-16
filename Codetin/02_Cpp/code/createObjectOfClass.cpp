#include <iostream>
using namespace std;

// Define a class
class Car {
public:
    string brand;
    int year;

    // Constructor
    Car(string b, int y) {
        brand = b;
        year = y;
    }

    // Member function
    void display() {
        // cout << "Brand: " << brand << ", Year: " << year << endl;
    }
};

int main() {
    // 1️⃣ Create object statically (on the stack)
    Car car1("Toyota", 2020);
    car1.display();

    // 2️⃣ Create object dynamically (on the heap)
    Car* car2 = new Car("Honda", 2022);
    car2->display();

    // Don’t forget to delete dynamic objects to free memory
    delete car2;

    return 0;
}
