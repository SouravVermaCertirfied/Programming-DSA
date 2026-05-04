// #include<iostream>
// using namespace std;

// class Person{
//     private:
//         int pid;
//     public:
//         Person(int id){
//             this->pid = id;
//         }
// };

// class Employee : public Person{
//     private:
//         int eid;
//     public:
//         Employee(int eid){
//             this->eid = eid;
//         }
// };

// class HR : public Employee{
//     private:
//         int dept;
//     public:
//         HR(int dept){
//             this->dept = dept;
//         }
//         void printHR(){
//             cout<<this->dept;
//         }
// };

// int main(){
//     HR hr(50);
//     hr.printHR();
//     return 0;
// }


#include<iostream>
using namespace std;

class Person{
    private:
        int pid;

};

class Employee : public Person{
    private:
        int eid;
    public:

};

class HR : public Employee{
    private:
        int dept = 50;
    public:

        void printHR(){
            cout<<this->dept;
        }
};

int main(){
    HR hr;
    hr.printHR();
    return 0;
}
