#include<iostream>
using namespace std;

class Person {
    private:
        int pid;
    public:
        Person(int id) {
            this->pid = id;
        }
};

class Employee : public Person {
    private:
        int eid;
    public:
        // Pass 'id' up to Person, then set 'eid'
        Employee(int id, int eid) : Person(id) {
            this->eid = eid;
        }
};

class HR : public Employee {
    private:
        int dept;
    public:
        // Pass 'id' and 'eid' up to Employee, then set 'dept'
        HR(int id, int eid, int dept) : Employee(id, eid) {
            this->dept = dept;
        }
        
        void printHR() {
            cout << "Dept ID: " << this->dept << endl;
        }
};

int main() {
    // Now providing all necessary IDs for the hierarchy
    HR hr(1, 101, 50); 
    hr.printHR();
    return 0;
}