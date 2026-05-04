/*
To demonstrate this, we need to create a Member class that prints a message whenever its default constructor is called.

When using Function Style, you will see "Inside Default Constructor" because the compiler initializes the member before you reach the {}. 
When using the Initializer List, the compiler skips the default and goes straight to the parameterized one.


Output:
+---------------------------------------------------------+
|SCENARIO A: Function Style                               |
|  >> Inside Default Constructor                          |
|--- Starting Function Style Body ---                     |
|  >> Inside Parameterized Constructor (Value: 10)        |
|                                                         |
|SCENARIO B: Initializer List Style                       |
|  >> Inside Parameterized Constructor (Value: 20)        |
|--- Starting Initializer List Body ---                   |
+---------------------------------------------------------+
*/


#include <iostream>
using namespace std;

class Member {
    int val;
public:
    // Default Constructor
    Member() {
        cout << "  >> Inside Default Constructor" << endl;
    }
    // Parameterized Constructor
    Member(int val) {
        cout << "  >> Inside Parameterized Constructor (Value: " << val << ")" << endl;
        this->val = val;
    }
    int getVal(){
        return val;
    }
};

class Example {
    Member m;
public:
    // 1. Function Style: m() is called automatically first!
    Example(int val, bool useFunctionStyle) {
        cout << "--- Starting Function Style Body ---" << endl;
        m = Member(val); // This is an assignment, not initialization
    }

    // 2. Initializer List: m(val) is called directly
    Example(int val) : m(val) {
        cout << "--- Starting Initializer List Body ---" << endl;
    }

    int gethisval(){
        return m.getVal();
    }
};

int main() {
    cout << "SCENARIO A: Function Style" << endl;
    Example ex1(10, true);

    cout << "\nSCENARIO B: Initializer List Style" << endl;
    Example ex2(20);

    cout<<ex2.gethisval();
    return 0;
}