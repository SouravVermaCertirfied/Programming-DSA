#include<iostream>
using namespace std;

class Person {
    protected:
        int pid;
    public:
        Person(int id) : pid(id) {
            cout << "[1. Person Constructor] Initializing PID to " << pid << endl;
        }
};

class Employee : public Person {
    protected:
        int eid;
    public:
        // Chains to Person first
        Employee(int id, int eid) : Person(id), eid(eid) {
            cout << "[2. Employee Constructor] Initializing EID to " << eid << endl;
        }
};

class HR : public Employee {
    private:
        int dept;
    public:
        // --- Constructor 1: Only Dept ---
        HR(int dept) : Employee(0, 0) {
            this->dept = dept;
            cout << "[3. HR Constructor] Dept Only mode. Set Dept to " << dept << endl;
            cout << "--------------------------------------" << endl;
        }

        // --- Constructor 2: Dept and EID ---
        HR(int dept, int eid) : Employee(0, eid) {
            this->dept = dept;
            cout << "[3. HR Constructor] Dept & EID mode. Set Dept to " << dept << endl;
            cout << "--------------------------------------" << endl;
        }

        // --- Constructor 3: All Three ---
        HR(int dept, int eid, int pid) : Employee(pid, eid) {
            this->dept = dept;
            cout << "[3. HR Constructor] Full Data mode. Set Dept to " << dept << endl;
            cout << "--------------------------------------" << endl;
        }

        void printInfo() {
            cout << "FINAL DATA -> Dept: " << dept << " | EID: " << eid << " | PID: " << pid << "\n" << endl;
        }
};

int main() {
    cout << "--- CREATING HR1 (Only Dept) ---" << endl;
    HR hr1(50);
    hr1.printInfo();

    cout << "--- CREATING HR2 (Dept & EID) ---" << endl;
    HR hr2(50, 101);
    hr2.printInfo();

    cout << "--- CREATING HR3 (All Three) ---" << endl;
    HR hr3(50, 101, 1);
    hr3.printInfo();

    return 0;
}