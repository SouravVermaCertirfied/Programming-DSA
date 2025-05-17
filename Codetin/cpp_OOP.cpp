/*


*/

#include<iostream>
using namespace std;

class Car{
    private:
        int mac;
    public:
        int vin;
        void setMac(int mac){
            this->mac = mac;
        }

        Car(int mac, int vin){
            this->mac = mac;
            this->vin = vin;
        }

        void printCar(){
            cout<<"mac is : "<<mac<<endl;
            cout<<"vin is : "<<vin<<endl;
            cout<<endl;
        }
};


class Ford{
    public:
    
}


int main(){
    int mac = 123;
    int vin = 567;
    Car *car = new Car(mac, vin);
    car->printCar();
}