# Friend Functions
> Friendship is granted, not taken.
The class which has to give friendship decides what it will share, not the class using the frined's shared item.

### Key points:
- Friendship is not inherited
- Frinedship is not translative
- Friendship is not mutual
- Frindship is granted, not taken

A single class member variable CANNOT to be friend, friendship is done at class and function levels.

### Making a function a friend
Uses forward declaration technqiue.  
Example:
```cpp
#include <iostream>
using namespace std;

class Employee; // Forward declaration

class Printer {
public:
    void printEmp(const Employee &e); // Declaration
};

class Employee {
private:
    int id;
    string name;

    // Granting friendship to printEmp function
    friend void Printer::printEmp(const Employee &e);

public:
    Employee(int i, string n) : id(i), name(n) {}
};

void Printer::printEmp(const Employee &e) {
    cout << e.id << " " << e.name << '\n'; // Accessing private members
}

int main() {
    Printer p;
    Employee e(101, "ABC");
    p.printEmp(e); // Output: 101 ABC
    return 0;
}
```

### Making a class a friend

```cpp
#include <iostream>
using namespace std;

class Printer; // Forward declaration

class Employee {
private:
    int id;
    string name;

    // Granting friendship to the Printer class
    friend class Printer;

public:
    Employee(int i, string n) : id(i), name(n) {}
};

class Printer {
public:
    void printEmp(const Employee &e) {
        cout << e.id << " " << e.name << '\n'; // Accessing private members
    }
};

int main() {
    Printer p;
    Employee e(101, "ABC");
    p.printEmp(e); // Output: 101 ABC
    return 0;
}
```

## Practicle use cases
Most popular are :
1. Operator overloading
2. Handle-Body coding style - where public facing classes handle classes that have lesser directly external interfaces.
3. Factory Classes : specific Factory class to be the only thing allowed to create objects of another class. You make the constructor of the target class private and declare the Factory as a friend. This prevents users from accidentally instantiating objects the wrong way.
4. Mathematical/Matrix Libraries
5. Unit Testing

### 1. Operator overloading

**A | Example: Overloading `<<` operator to output members of a class.**  
<details><summary>Code Here</summary>

```cpp
#include<iostream>
using namespace std;

class Person{
    private:
		int pass = 1234;
		string name = "Verma Daws";
	public:
		friend ostream& operator<<(ostream& os, const Person& P);
};

ostream& operator<<(ostream& os, const Person& p){
	os<<p.name<<" "<<p.pass;
	return os;
}

int main(){
	Person p;
	cout<<p<<endl;
	return 0;
}


```

</details>


> **Can you write this without `friend` keyword ?**  
Yes, you can absolutely do this without the friend keyword. However, there is a catch: you must provide a public way to access the private data.

<details><summary>Code here</summary>

```cpp

#include <iostream>
#include <string>
using namespace std;

class Person {
    private:
        int pass = 1234;
        string name = "Verma Daws";

    public:
        // Public methods to access private data
        string getName() const { return name; }
        int getPass() const { return pass; }
};

// Now this function doesn't need to be a 'friend'
ostream& operator<<(ostream& os, const Person& p) {
    os << p.getName() << " " << p.getPass();
    return os;
}

int main() {
    Person p;
    cout << p << endl;
    return 0;
}

```

</details>

---

**B | Example: Overloading `+` operator to Add two complex numbers.**  

<details><summary>Code Here</summary>

```cpp
#include<iostream>
using namespace std;

class Complex{
    private:
		int real;
		int img;
	public:
		Complex(int real = 0, int img = 0){
			this->real = real ;
			this->img = img;
		}
		friend Complex operator+(Complex a, Complex b);

};

Complex operator+(Complex a, Complex b){
	return Complex(a.real + b.real, a.img + b.img);
}

int main(){
	Complex c1(1,2), c2(6,7);
	Complex c3 = c1 + c2;
	return 0;
}

```

</details>