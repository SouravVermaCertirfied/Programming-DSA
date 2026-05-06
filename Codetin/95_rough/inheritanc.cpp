#include<iostream>
using namespace std;

class Person{
    int adhar = 123;
    public:
        // Person(int ad) : adhar(ad) {}
        virtual int getAdhar(){
            return adhar;
        }
};

class Employee : public Person{
    int empid;
    public:
        int getEmpid(){
            return empid;
        }
};

class Citizen : public Person{
    int voterid = 98;
    public:
        int getvoterid(){
            return voterid;
        }
};

class Engineer : public Employee , public Citizen{
    int seatno;
    public:
        int getseatno(){
            return seatno;
        }
};

int main(){
    Engineer e1;
    cout<<e1.getAdhar()<<endl<<e1.getvoterid()<<endl;
    cout<<"Running program";
    return 0;
}