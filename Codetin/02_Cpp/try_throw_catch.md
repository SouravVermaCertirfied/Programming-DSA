### Simple try throw catch blocks

```c
#include<iostream>
using namespace std;

int myfun(int a, int b){
    if(b==0)
        throw 0;
    return a/b;
}

int main(){
    int a = 0;
    int b = 0;

    try{
        myfun(a,b);
    }
    catch(int e){
        cout<<"this is not good";
    }
    cin.get();
    return 0;
}

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 0;

    try {
        if (b == 0) {
            throw 0;  // throw an int for divide by zero
        }
        int result = a / b;  // safe division
        cout << "Result: " << result << endl;
    }
    catch (int e) {  // catch the thrown int
        cout << "Caught exception: Division by zero! Error code = " << e << endl;
    }

    cout << "Program continues normally." << endl;
    return 0;
}
```

### Throwing user-defined classes
```cpp

#include<iostream>
using namespace std;

class Coolexp {};

int main(){
    int a = 0, b = 0;
    Coolexp e1;

    try{
        if(b==0) throw e1;
    }
    catch(Coolexp e1){
        cout<<"found you";
    }
    cin.get();
    return 0;
}

```

### Throwing user-define classes using exception

```cpp

#include<iostream>
#include<exception> // for exception class
using namespace std;

class MyException : public exception {
    virtual const char *what() const throw(){
        return "excption occured";
    }
};

int main(){
    try{
        throw MyException();
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
    cin.get();
    return 0;
}
 
```